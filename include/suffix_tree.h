#include <string>
//#include <tr1/unordered_map>
#include <limits>
#include <map>
#include <vector>
#include <iostream>
#include <stdexcept>

using std::vector;
using std::string;
using std::map;
using std::make_pair;
using std::cout;
using std::endl;
using std::out_of_range;
using std::ostream;
//typedef tr1::unordered_map map;

// TODO: upgrade it to process trace. Rule: char-->elem  string-->elem_list
class SuffixTree
{
public:
	// active point is initialized as (root, None, 0), remainder initialized as 1
	SuffixTree(string str):test_str(str), root(test_str), active_point(&root, 0, 0), remainder(0), pos(0), active_e(0), ls() {}
	int construct(void);

	// return -1 if no such sub exist, return the beginning position of this substring in thr original string if it exist
	int search(string sub);

	// return the length of the longest prefix of sub which can be matched in suffix tree
	template <class Iterator>
	Iterator inc_search(Iterator sub)
	{
		Iterator result = sub;
		Node* node = &root;
		Edge* edge = NULL;
		int pos = 0;	// the iter's pos at edge
		int edge_len = -1;
		bool flag = true;


		while (flag) {
			if (edge == NULL) {
				edge = node->find_edge(*result);	
				if (edge == NULL) {
					flag = false;
				}
				else {
					result++;
					pos = 1; // the second element of the edge
					edge_len = edge->length();
				}
			}
			else {
				if (pos >= edge_len) {
					node = edge->endpoint;
					edge = NULL;
					edge_len = 0;
				}
				else {
					if (*result == (*edge)[pos]) {
						result++;
						pos++;
					}
					else
						flag = false;
				}
			}
		}
		
		return result;
	}

	struct Node;
	struct Edge{
		// the begin and end pos of this edge, note that INT_MAX stands for #(the changing end pos of this entire string)
		unsigned int begin, end;
		// Is there a better way to find test_str?
		string& test_node_str;

		Node * endpoint;

		Edge(unsigned int b, unsigned int e, string& str):
			test_node_str(str) 
		{
			begin = b;
			end = e;
			endpoint = NULL;
			std::cout << "Edge initialized" << std::endl;
		}

		void change_edge(unsigned int b, unsigned int e)
		{
			begin = b;
			end = e;
		}

		int length(void) 
		{

			if (end > test_node_str.size())
				return test_node_str.size() - begin;
			else
				return end - begin + 1; 
		}
		
		// needed by map
		friend bool operator<(const Edge& me, const Edge& other)
		{
			return me.begin < other.begin;
		}

		char operator[](unsigned int i)
		{
			i += begin;
			if (i > end)
				throw out_of_range("Edge [] out of range.");

			return test_node_str[i];
		}

		friend ostream& operator<<(ostream& os, Edge& edge)
		{
			unsigned int end = edge.test_node_str.size()-1;
			if (end >= edge.end)
				end = edge.end;

			char c;
			for (unsigned int i=edge.begin; i<=end; i++) {
				c = edge.test_node_str[i];
				os << c;
			}
			if (end != edge.end)
				os << '#';

			return os;
		}

		bool is_none(void) { return begin == 0 && end == 0; }
	};

	struct Node{
		string& test_node_str;
		map<int, int> testmap;
		map<Edge*, bool> edges;
		// find the edge quicky by storing the leading char of this edge
		map<char, Edge*> findedges;
		Node* suffix_link;

		friend class LinkState;

		Node(string& str) : 
			test_node_str(str), suffix_link(NULL) { edges.clear(); findedges.clear(); }

		void add_edge(Edge* edge) { 
			if (edge->endpoint == NULL)
				edge->endpoint = new Node(test_node_str);
			make_pair(edge, true);
			edges.insert(make_pair(edge, true)); 
			findedges.insert(make_pair(test_node_str[edge->begin], edge));
			cout << "edge added. Now we have " << edges.size() << "edges." << endl;
		}

		void del_edge(Edge* edge) {
			map<Edge*, bool>::iterator iter = edges.find(edge);

			if (iter == edges.end())
				throw out_of_range("edge don't exit");
			else {
				// note we should erase the findedges too
				edges.erase(edge);
				cout << "delete" << (*edge)[0] << endl;
				findedges.erase((*edge)[0]);
				cout << "edge deleted. Now we have " << edges.size() << "edges." << endl;
			}

		}

		// find edge by the first char
		Edge* find_edge(char c)
		{
			cout << "finding edge char " << c;
			map<char, Edge*>::iterator iter = findedges.find(c);
			cout << " founded? ";

			if (iter != findedges.end()) {
				cout << "yes." << endl;
				return iter->second;
			}
			else {
				cout << "no." << endl;
				return NULL;
			}
		}

		bool isleaf() { return edges.empty(); }

		bool operator==(Node& other)
		{
			return (this) == (&other);
		}

		friend ostream& operator<<(ostream& os, Node& node)
		{
			map<Edge*, bool>::iterator iter;
			map<char, Edge*>::iterator iter_f;

			for (iter=node.edges.begin(); iter!=node.edges.end(); ++iter)
				os << iter->first << '\t';
			os << endl;
			
			for (iter_f=node.findedges.begin(); iter_f!=node.findedges.end(); ++iter_f)
				os << iter_f->first << "-->" << iter_f->second << endl;

			return os;
		}
	};
	int print_tree(void);
private:
	string test_str;
	class ActivePoint{
	public:
		Node* active_node;
		char active_edge;
		int active_length;

		ActivePoint(Node* node, char edge, int length): 
			active_node(node), active_edge(edge), active_length(length) { std::cout << "ActivePoint initialized" << std::endl; }
	};

	Node root;
	ActivePoint active_point;

	Node* get_active_node(void) { return active_point.active_node; }
	void set_active_node(Node* node) { active_point.active_node = node; cout << "Active node set as " << node << endl; }
	char get_active_edge(void) 
	{ 
		return test_str[active_e]; 
	}

	int get_active_length(void) { return active_point.active_length; }
	void set_active_length(int len) { active_point.active_length = len; }
	void inc_active_len() { active_point.active_length++; }
	void dec_active_len() { active_point.active_length--; }
	
	// how many suffixes is to be inserted?
	int remainder;
	// how many characters inserted?
	unsigned int pos;
	unsigned int active_e;	// the beginning position of suffixes need to be inserted
	char get_ele(int i) { return test_str[i]; }
	// insert a char from pos to suffix tree
	int insert();
	int insert_rule1();
	int insert_rule3();
	int print_node(Node* node, int level);


	Node* separate_edge(Node * node, Edge* edge);

	// check if we can change active node
	bool check_active_node(void)
	{
		Node* node = get_active_node();
		char a_char = get_active_edge();
		Edge* edge = node->find_edge(a_char);

		if (edge == NULL)
			return false;

		unsigned int edge_size = edge->end - edge->begin + 1;
		unsigned int length = get_active_length();
		
		// update
		if (length >= edge_size) {
			set_active_node(edge->endpoint);
			set_active_length(length-edge_size);
			active_e += edge_size;
			
			return true;
		}
		return false;
	}

	// this class indicate when shall we insert a suffix link
	// ls should be a singleton
	class LinkState
	{
		bool first;
		
		Node* prev, *curr;

	public:
		LinkState() : first(true), prev(NULL), curr(NULL) {}

		void ins_link(Node* node)
		{
			prev = curr;
			curr = node;
			
			if (first == false) {
				prev->suffix_link = curr;
				cout << "Suffix link added from prev " << prev << " to curr " << curr << endl;
			}

			first = false;
		}

		void clear(void)
		{
			first = true;
			prev = curr = NULL;
		}
	};
	LinkState ls;
};
