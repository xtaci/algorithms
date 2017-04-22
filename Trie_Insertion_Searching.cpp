#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#define get_index(c) (int(tolower(c)-'a'))
using namespace std;
struct TrieNode // defining the trie node
{
	vector<TrieNode *>children = vector<TrieNode *>(26,nullptr); // a vector of map with key being the 26 chars and the value being a node
	bool isend; // isend deonates the end of the word.
};
TrieNode *get_node()
{
	TrieNode *new_node = new TrieNode;
	new_node->isend = false;
	return new_node;
}
void insert(TrieNode *root, const string &test) //  a utility function to insert new string to the trie
{
	size_t size = test.length();
	TrieNode *crawl = root;
	for(size_t i = 0; i < size; ++i)
	{
		auto index = get_index(test[i]);
		if(!crawl->children[index])
			crawl->children[index] = get_node();
		crawl = crawl->children[index];
	}
	crawl->isend = true;
}
bool prefix_search(TrieNode *root, const string &sample) // a utility function to search for a prefix
{
	size_t size = sample.length();
	TrieNode *crawl = root;
	for(size_t i = 0; i < size; ++i)
	{
		auto index = get_index(sample[i]);
		if(!crawl->children[index])
			return false;
		crawl = crawl->children[index];
	}
	return true;
}
bool word_search(TrieNode *root, const string &sample) // A utility function to search for an entire word.
{
	size_t size = sample.length();
	TrieNode *crawl = root;
	for(size_t i = 0; i < size; ++i)
	{
		auto index = get_index(sample[i]);
		if(!crawl->children[index])
			return false;
		crawl = crawl->children[index];
	}
	return crawl->isend;
}
string res(bool test)
{
	if(test)
		return "is present in the Dictionary";
	return "is not present in the Dictionary";
}
int main()
{
	vector<string>string_list;
	string temp;
	unsigned long long int i;
	cout<<"Enter number of strings to be entered: ";
    cin>>i;
    cout<<"Enter strings: ";
    while(i--)
    {
        cin>>temp;
        string_list.push_back(temp);
    }
	TrieNode *root = get_node();
	for(auto i = string_list.begin(); i != string_list.end(); ++i)
		insert(root,*i);
    cout<<"Enter string to be searched: ";
    cin>>temp;
	cout<<"String "+temp+" "<<res(word_search(root,temp));
}
