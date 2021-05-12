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
	using std::numeric_limits;

	while (pos < test_str.size()) {
		ls.clear();
		remainder++;
		cout << "Char:  "  << test_str[pos] << endl;

		while (remainder) {
			int length = get_active_length();
			if (length == 0)
				active_e = pos;

			Node* node = active_point.active_node;
			char a_char = get_active_edge();
			Edge* a_edge = node->find_edge(a_char);


			if (a_edge == NULL) {
				Edge* newedge = new Edge(pos, numeric_limits<unsigned int>::max(), test_str);
				node->add_edge(newedge);
				ls.ins_link(node);
			}	
			else {
				if (check_active_node())
					continue;

				char expected_ele = (*a_edge)[get_active_length()];
				if (expected_ele == get_ele(pos)) {
					inc_active_len();
					ls.ins_link(node);
					break;
				}
				Node *newnode = separate_edge(node, a_edge);
				Edge* newedge = new Edge(pos, numeric_limits<unsigned int>::max(), test_str);
				newnode->add_edge(newedge);
				ls.ins_link(newnode);
			}
			remainder--;
			if (node == &root && get_active_length() > 0) {
				dec_active_len();
				active_e = pos - remainder + 1;
			}
			else if (node->suffix_link) {
				set_active_node(node->suffix_link);
			}
			else
				set_active_node(&root);
		}

		pos++;
	}
	return 0;
}

SuffixTree::Node* SuffixTree::separate_edge(Node * node, Edge* a_edge)
{
	cout << "separate the old edge here: " << (*a_edge) << endl;
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
	cout << "Beginning" << endl;
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
