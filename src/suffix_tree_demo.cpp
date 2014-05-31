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
		cout << "Char:  "  << test_str[pos] << endl;
		cout << "Suffix yet inserted begin at " << base_pos << " " << test_str[base_pos] << endl;

		int move = 0;
		while (move == 0)
			move = insert();
		pos++;
	}
	return 0;
}

int SuffixTree::insert(void)
{
	using std::numeric_limits;

	int move = 1;

	Node* node = active_point.active_node;
	int length = get_active_length();

	Edge* a_edge = get_active_edge();

	if (a_edge == NULL) {
		Edge *search_edge = node->find_edge(get_ele(pos));
		
		if (search_edge == NULL) {
			// insert new suffix
			Edge *new_edge = new Edge(pos, numeric_limits<unsigned int>::max(), test_str);
			node->add_edge(new_edge);
			remainder--;
			if (node->suffix_link) {
				// move to suffix link
				set_active_node(node->suffix_link);
				Edge *new_active_edge = node->suffix_link->find_edge(base_pos);
				set_active_edge(new_active_edge);
				move = 0;
			}
			else {
				// move to root
				set_active_node(&root);

				if (base_pos != pos) {
					Edge *new_active_edge = root.find_edge(get_ele(base_pos));
					set_active_edge(new_active_edge);
					dec_active_len();
				}
				base_pos++;

				if (remainder > 0) {
					move = 0;
				}
				else
					move = 1;
			}
		}
		else {
			// set new active edge
			set_active_edge(search_edge);
			inc_active_len();
			move = 1;
		}
	}
	else {
		char expected_ele = (*a_edge)[get_active_length()];

		cout << (*a_edge) << endl;
		cout << get_active_length() << endl;
		cout << expected_ele << " vs " << get_ele(pos) << endl;
		if (expected_ele == get_ele(pos)) {
			// expand active length
			inc_active_len();
			check_active_node();
			move = 1;
		}
		else {
			// seperate edge and insert new suffix
			Node * new_node = seperate_edge(node, a_edge, length);
			Edge *new_edge = new Edge(pos, numeric_limits<int>::max(), test_str);
			new_node->add_edge(new_edge);
			remainder--;
			ls.ins_link(new_node);

			if (new_node->suffix_link) {
				// move to suffix link
				set_active_node(node->suffix_link);
				Edge *new_active_edge = node->suffix_link->find_edge(get_ele(base_pos));
				set_active_edge(new_active_edge);
				move = 0;
			}
			else {
				// fall back to root
				set_active_node(&root);
				dec_active_len();
				base_pos++;
				if (base_pos != pos) {
					Edge *new_active_edge = root.find_edge(get_ele(pos-remainder+1));
					set_active_edge(new_active_edge);
					base_pos = pos - remainder + 1;

					set_active_length(pos-base_pos);
					check_active_node();

					move = 0;
				}
				else {
					set_active_edge(NULL);
					move = 0;
				}
			}

		}
	
	}
	return move;
}

SuffixTree::Node* SuffixTree::seperate_edge(Node * node, Edge* a_edge, int rule)
{
	cout << "seperate the old edge here: " << (*a_edge) << endl;
	int new_begin = a_edge->begin + get_active_length();
	int new_end = a_edge->end;

	int old_begin = a_edge->begin;
	int old_end = new_begin - 1;

	cout << (*node);

	node->del_edge(a_edge);
	a_edge->change_edge(new_begin, new_end);
	Edge* old_edge1 = new Edge(old_begin, old_end, test_str);
	node->add_edge(old_edge1);

	old_edge1->endpoint->add_edge(a_edge);

	cout << "The old edge split as -- " << (*a_edge) << " and -- " << (*old_edge1) << endl;

	cout << "root " << (&root) << endl;
	cout << node << endl;
	Node* new_node = old_edge1->endpoint;
	cout << node << endl;

	return new_node;
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
	SuffixTree st("mississippi");

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
