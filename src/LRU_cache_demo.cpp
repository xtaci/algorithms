
#include <iostream>
#include "LRU_cache.h"

using namespace std;
int main() {
#if 1
	alg::LRUCache *cache=new alg::LRUCache(9);

	cache->putValue(1,1);
	cache->putValue(2,2);
	cache->putValue(3,3);
	cache->putValue(4,3);
	cache->putValue(5,2);
	cache->displayNodes();

	cout << cache->getValue(4) << endl;
	cache->displayNodes();
	//cache->displayNodes();
	cout << cache->getValue(3) << endl;	
	cache->displayNodes();
	cout << cache->getValue(3) << endl;	
	cache->displayNodes();
	cout << cache->getValue(1) << endl;	
	cache->displayNodes();
	cout << cache->getValue(2) << endl;
	cache->displayNodes();	
	cout << cache->getValue(9) << endl;	

	cache->displayNodes();

	cache->putValue(4,9);
	//cout << cache->getValue(2) << endl;
	//cout << cache->getValue(3) << endl;
	cache->displayNodes();
	cout << cache->getValue(4) << endl;	
	cache->displayNodes();
	cout << cache->getValue(2) << endl;	
	cache->displayNodes();

	delete cache;
#endif
	return 1;
}
