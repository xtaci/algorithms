#include "suffix_tree.h"
#include <iostream>

int SuffixTree::search(string sub)
{
	Node* node = &root;
	bool in_edge = false; // Are we searching in middle of an edge?
	Edge* edge = NULL;
	int edge_pos = 0, edge_len = 0;

	int result = -1;

	for (unsigned int i=0; i<sub.size(); i++) {
		char cur = sub[i];

		if (in_edge == false) {
			in_edge = true;
			edge = node->find_edge(cur);	// find an edge and search it

			if (edge == NULL)
				return -1;
			
			// record match pos
			if (i == 0)
				result = edge->begin;

			edge_pos = 0;
			edge_len = edge->length();
		}

		
		if (cur != (*edge)[edge_pos])
			return -1;

		edge_pos++;
		// reached the end of this edge, jump to next node
		if (edge_pos >= edge_len) {
			in_edge = false;
			node = edge->endpoint;
			edge = NULL;
			edge_pos = 0;
		}
	}

	return result;
}


int SuffixTree::construct(void)
{
	// test_str shouldn't have '#' until now
	test_str = test_str + "#";

	while (pos < test_str.size()) {
		ls.clear();
		remainder++;
		//cout << "Char:  "  << test_str[pos] << endl;

		bool flag = true;
		while (flag)
			flag = insert();
		pos++;
	}
	return 0;
}

int SuffixTree::insert(void)
{
	int result = 0;

	Node* node = active_point.active_node;
	if (node == (&root)) {
		//cout << "ActiveNode is root." << endl;
		result = insert_rule1();	
	}
	else {
		//cout << "ActiveNode isn't root." << endl;
		result = insert_rule3();
	}

	return result;
}

// rule1 applies when the active node is root
int SuffixTree::insert_rule1(void)
{
	using std::numeric_limits;
	
	//cout << "Rule 1" << endl;
	Node* node = &root;

	Edge* a_edge = node->find_edge(get_active_edge());

	// next active edge
	char active_char = 0;

	// can we find a match at active node?
	Edge* possible = NULL;
	bool will_insert = false;
	if (get_active_length() != 0 && a_edge != NULL) {
		// shouldn't throw out_of_range here, e.g. abcabc*
		char match_char = (*a_edge)[get_active_length()];
		if (match_char == get_ele(pos))
			possible = a_edge;
		else
			will_insert = true;	// will insert while active length is not 0 and activechar don't match
		//cout << "Active char is " << active_char << endl;

		// node for insertion
	}
	else if (get_active_length() == 0) {
		//cout << "Active char is NULL." << endl;
		possible = node->find_edge(get_ele(pos));

		// new active edge here and only here!
		if (possible)
			active_char = get_ele(pos);
		else
			active_char = 0;
	}
	else {
		cout << "Error!!!!!!!!!!!!!!!!!!!1" << endl;
		//throw;
	}

	
	if (possible) {
		remainder++;

		// if not 0, then it's not a new edge, should not set
		if (get_active_length() == 0)
			set_active_edge(active_char);

		inc_active_len();
		check_an();
	}
	else {
		// seperate the old edge, set new active edge
		if (a_edge != NULL) {
			node = seperate_edge(node, a_edge, 1);
		}
		else
			set_active_edge(0);

		//cout << "append a new edge at endpoint" << endl;
		Edge* new_edge2 = new Edge(pos, numeric_limits<int>::max(), test_str);
		//cout << node << endl;
		node->add_edge(new_edge2);
	}

	remainder--;
	
	return will_insert;
}

SuffixTree::Node* SuffixTree::seperate_edge(Node * node, Edge* a_edge, int rule)
{
	//cout << "seperate the old edge here: " << (*a_edge) << endl;
			
	char active_char;
	 
	if (remainder > 2)
		active_char = (*a_edge)[1];
	else 
		active_char = get_ele(pos);

	int new_begin = a_edge->begin + get_active_length();
	int new_end = a_edge->end;

	int old_begin = a_edge->begin;
	int old_end = new_begin - 1;

	//cout << node->find_edge(active_char) << "|||||||||||||||||||||||||| char " << active_char << endl;
	//cout << (*node);

	node->del_edge(a_edge);
	a_edge->change_edge(new_begin, new_end);
	Edge* old_edge1 = new Edge(old_begin, old_end, test_str);
	node->add_edge(old_edge1);
	//cout << node->find_edge(active_char) << "||||||||||||||||||||||||||2 char " << active_char << endl;

	old_edge1->endpoint->add_edge(a_edge);
	//cout << (*node);
//	old_edge1->endpoint->suffix_link = a_edge->endpoint->suffix_link;
//	a_edge->endpoint->suffix_link = NULL;
/*-----------------------------------------------------------------------
	Edge* new_edge1 = new Edge(new_begin, new_end, test_str);
	a_edge->endpoint->add_edge(new_edge1);
------------------------------------------------------------------*/

	//cout << "change edge" << endl;

	//cout << "What's wrong?" << endl;
	cout << "The old edge split as -- " << (*a_edge) << " and -- " << (*old_edge1) << endl;
	//cout << "What's wrong?" << endl;
			
	if (rule == 1) {
		set_active_edge(active_char);
		dec_active_len();
	}
	else if (rule == 3) {
		Node* n = &root;	// new active node
		//cout << node;
		if (node->suffix_link) {
			n = node->suffix_link;
			cout << " Moved to suffix link!--------------" << endl;
		}
		else
			cout << " Moved to root!------------------" << endl;
		set_active_node(n);
	}

	cout << "root " << (&root) << endl;
	//cout << node << endl;
	Node* new_node = old_edge1->endpoint;
	ls.ins_link(new_node);
	//cout << node << endl;

	return new_node;
}

// applies when the active is not root
int SuffixTree::insert_rule3()
{
	//cout << "Rule3" << endl;
	Node * node = get_active_node();
	cout << "Active node " << node << endl;
	Edge * edge = node->find_edge(get_active_edge());

	// input match a suffix?
	bool match = false;
	if (get_active_length() == 0) {
		if (node->find_edge(get_ele(pos))) {
			match = true;

			set_active_edge(get_ele(pos));
			inc_active_len();
			check_an();
		}
	}
	else {
		// assert edge is not NULL
		char match_char = (*edge)[get_active_length()];
		if (match_char == get_ele(pos)) {
			match = true;

			inc_active_len();
			check_an();
		}
	}

	if (match)
		return 0;

	if (edge != NULL) {
		node = seperate_edge(node, edge, 3);
	}

	using std::numeric_limits;

	//cout << "append a new edge at endpoint" << endl;
	Edge* new_edge2 = new Edge(pos, numeric_limits<int>::max(), test_str);
	cout << node << endl;
	node->add_edge(new_edge2);

	remainder--;

	return 1;	// should insert again at a different node
	
}

int SuffixTree::print_tree()
{
	print_node(&root, 1);

	return 0;
}

int SuffixTree::print_node(Node* node, int level)
{
	using namespace std;
	if (level == 0) 
		cout << "Root " << endl;

	if (node->isleaf()) {
		cout << "Leaf reached." << endl;
		return 0;
	}
	
	map<Edge*, bool>::iterator iter;
	for (iter = node->edges.begin(); iter!=node->edges.end(); iter++) {
		int indent = level;
		while (indent--) 
			cout << '\t';
	
		int begin = iter->first->begin, end = (iter->first->end < test_str.size() - 1) ? iter->first->end : test_str.size() - 1;
		cout << "--> (" << begin << ", " << end << ")  ";
		for (int i=begin; i<=end; i++)
			cout << test_str[i];
		cout << endl;

		cout << "Node Add " << node << endl;
		cout << "Edge printed " << iter->first << endl << endl;
		print_node((iter->first->endpoint), level+1);
	}

	cout << endl;
	return 0;
}

using namespace std;

int main()
{
	cout << "Begining" << endl;
	SuffixTree st("BANANAS");

	cout << "Constructing..." << endl;
	st.construct();

	cout << "Printing..." << endl;
	st.print_tree();

	cout << "Search ANA:" << st.search("ANA") << endl;
	cout << "Search NA:" << st.search("NA") << endl;
	cout << "Search NAN:" << st.search("NAN") << endl;
	cout << "Search B:" << st.search("B") << endl;

	cout << endl;

	cout << "Search BB:" << st.search("BB") << endl;
	cout << "Search ANN:" << st.search("ANN") << endl;
	cout << "Search b:" << st.search("b") << endl;

	return 0;
}
