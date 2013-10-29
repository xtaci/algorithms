
#include <iostream>
#include "LRU_cache.h"

using namespace std;
using namespace alg;

int main() {
		
		
	LRUCache<string,string> Cache(5);
	Cache.putValue("key1","value1");
	Cache.putValue("key2","value2");
	Cache.putValue("key3","value3");
	Cache.putValue("key4","value4");
	Cache.putValue("key5","value5");
	Cache.putValue("key6","value6");
	
	
	cout << "Display The LRU Cache...." << endl;
	Cache.display();
	
	cout << "Now,Visit the LRU Cache with \"key4\"" << endl;
	cout << "The \"key4\" Value is : "<< Cache.getValue("key4") << endl;
	cout << "The New LRU Cache is ... " << endl;
	Cache.display();
	
	cout << "Now, Update The LRU Cache with \"key5\" and new value is \"newValue5\" ... " << endl;
	Cache.putValue("key5","newValue5");
	cout << "The New LRU Cache is ... " << endl; 
	Cache.display();
	Cache.getValue("aaa");
	

}
