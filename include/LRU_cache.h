/*******************************************************************************
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * Least Recently Used (LRU): 
 * 	discards the least recently used items first. This algorithm requires 
 * keeping track of what was used when, which is expensive if one wants to make 
 * sure the algorithm always discards the least recently used item. General 
 * implementations of this technique require keeping "age bits" for cache-lines 
 * and track the "Least Recently Used" cache-line based on age-bits. In such an 
 * implementation, every time a cache-line is used, 
 * the age of all other cache-lines changes
 *  
 *  We use this double list to store the cache like this:
 * 
 *  NodeHead <==> Node1 <==> Node2 <==> ... ... <==> NodeN <==>NodeNear
 * 
 *  the "NodeHead" and "NodeNear" have no data , them just for head and near.
 * 
 *  Two Interface:
 *      getValue : get the value by key ,and put the Node to first
 *      putValue : add or update the Node's Key and Value, and then, 
 *                 put the Node to first
 * 
 * http://en.wikipedia.org/wiki/LRU_cache#Least_Recently_Used
 * 
 ******************************************************************************/

#ifndef _LRUCACHE_
#define _LRUCACHE_

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

using namespace std;

namespace alg {
	template<typename K,typename V>
		class LRUCache {
			typedef struct _Node_{
				K key;
				V value;

				struct _Node_ *next;
				struct _Node_ *pre;
			} CacheNode;

		public:
			LRUCache(int cache_size=10) {
				cache_size_ = cache_size;
				p_cache_list_head = new CacheNode();
				p_cache_list_near = new CacheNode();
				p_cache_list_head->next = p_cache_list_near;
				p_cache_list_head->pre = NULL;
				p_cache_list_near->pre = p_cache_list_head;
				p_cache_list_near->next = NULL;
			}

			~LRUCache() {
				CacheNode *p;
				p = p_cache_list_head->next;
				while(p!=NULL) {	
					delete p->pre;
					p=p->next;
				}

				delete p_cache_list_near;
				cache_hash.clear();
			}

			V getValue(K key) {
				//put the value in front of the list if find the key
				if(cache_hash.find(key) != cache_hash.end()){
					CacheNode *p=cache_hash[key];
					detachNode(p);
					addFristNode(p);
					return (cache_hash[key]->value);
				}else{

					cout << "[ERROR]No key with name ::" << key << endl;
					return V();
				}

			}

			bool putValue(K key,V value) {
				if (cache_hash.find(key) != cache_hash.end()) {
					cache_hash[key]->value=value;
					detachNode((CacheNode *)cache_hash[key]);
					addFristNode((CacheNode *)cache_hash[key]);
					if (cache_hash.size()>cache_size_) {
						delEndNode();					
					}
				} else {
					CacheNode *p=new CacheNode();
					p->key=key;
					p->value=value;
					addFristNode(p);
					cache_hash[key]=p;
					if(cache_hash.size()>cache_size_){
						cout << "[INFO]LRU Cache is full ... Delete Last One..." << endl;
						delEndNode();
					}
				}

				return true;	
			}

			void display(){	
				CacheNode *p=p_cache_list_head->next;
				while(p->next!=NULL) {
					std::cout << " KEY[" << p->key << "]<==>VALUE[" << p->value <<"]" << std::endl; 
					p=p->next;
				}
				std::cout << std::endl;			
			}

		private:
			int cache_size_;
			CacheNode *p_cache_list_head;
			CacheNode *p_cache_list_near;
			map<K,CacheNode*>cache_hash;


			void detachNode(CacheNode *node){
				node->pre->next=node->next;
				node->next->pre=node->pre;		
			}

			void addFristNode(CacheNode *node){
				node->pre=p_cache_list_head;			
				if(cache_hash.empty()) {
					node->next=p_cache_list_near;
					p_cache_list_near->pre=node;
					p_cache_list_head->next=node;
				} else {
					node->next=p_cache_list_head->next;
					p_cache_list_head->next->pre=node;
					p_cache_list_head->next=node;
				}
			}

			void delEndNode(){
				CacheNode *p=p_cache_list_near->pre;
				detachNode(p);
				cout << "[INFO]Delete key ::: " << p->key <<endl;
				cache_hash.erase(p->key);
				free(p);
			}
		};
}

#endif
