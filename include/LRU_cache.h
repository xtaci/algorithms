
/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * Least Recently Used (LRU): 
 * 	discards the least recently used items first. This algorithm requires keeping track of what was used when, 
 * which is expensive if one wants to make sure the algorithm always discards the least recently used item. 
 * General implementations of this technique require keeping "age bits" for cache-lines and track the 
 * "Least Recently Used" cache-line based on age-bits. In such an implementation, every time a cache-line is used, 
 * the age of all other cache-lines changes
 *  
 *  
 *  We use this double list to store the cache like this:
 * 
 *  NodeHead <==> Node1 <==> Node2 <==> ... ... <==> NodeN <==>NodeNear
 * 
 *  the "NodeHead" and "NodeNear" have no data , them just for head and near.
 * 
 *  Tow Interface:
 *      getValue : get the value by key ,and put the Node to first
 *      putValue : add or update the Node's Key and Value, and then, put the Node to first
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

using namespace std;

typedef struct _Node_{

	int key;
	int value;
	
	struct _Node_ *next;
	struct _Node_ *pre;

}CacheNode;



class LRUCache{
	
public:
	
	LRUCache(int cache_size=10)
		{
			cache_size_=cache_size;
			cache_real_size_=0;
			p_cache_list_head=new CacheNode();
			p_cache_list_near=new CacheNode();
			p_cache_list_head->next=p_cache_list_near;
			p_cache_list_head->pre=NULL;
			p_cache_list_near->pre=p_cache_list_head;
			p_cache_list_near->next=NULL;
	
		}
	~LRUCache()
		{
			CacheNode *p;
			p=p_cache_list_head->next;
			while(p!=NULL)
			{	
				delete p->pre;
				p=p->next;
			}

			delete p_cache_list_near;
		}


	int getValue(int key)
		{
			CacheNode *p=p_cache_list_head->next;	
			while(p->next!=NULL)
			{
				
				if(p->key == key) //catch node
				{
					
					detachNode(p);
					addToFront(p);
					return p->value;
				}	
				p=p->next;	
			}
			return -1;
		}

	bool putValue(int key,int value)
		{
			CacheNode *p=p_cache_list_head->next;
			while(p->next!=NULL)
			{
				
				
				if(p->key == key) //catch node
				{
					p->value=value;
					getValue(key);
					return true;
				}	
				p=p->next;	
			}
			
			
			if(cache_real_size_ >= cache_size_)
			{
				cout << "free" <<endl;
				p=p_cache_list_near->pre->pre;
				delete p->next;
				p->next=p_cache_list_near;
				p_cache_list_near->pre=p;
			}
			
			p=new CacheNode();//(CacheNode *)malloc(sizeof(CacheNode));
			
			if(p==NULL)
				return false;

			addToFront(p);
			p->key=key;
			p->value=value;
				
			cache_real_size_++;
				
			return true;	
		}
	void displayNodes()
		{
			CacheNode *p=p_cache_list_head->next;
			
			while(p->next!=NULL)
			{
				cout << " Key : " << p->key << " Value : " << p->value << endl; 
				p=p->next;
				
			}
			cout << endl;
		
		}
	
	
private:
	
	int cache_size_;
	int cache_real_size_;
	CacheNode *p_cache_list_head;
	CacheNode *p_cache_list_near;
		
	void detachNode(CacheNode *node)
		{
			node->pre->next=node->next;
			node->next->pre=node->pre;
		}
	void addToFront(CacheNode *node)
		{
			
			node->next=p_cache_list_head->next;
			p_cache_list_head->next->pre=node;
			p_cache_list_head->next=node;
			node->pre=p_cache_list_head;

		}

};



#endif



