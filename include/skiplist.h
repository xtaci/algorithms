/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * SKIP LIST
 *
 * http://en.wikipedia.org/wiki/Skip_list
 *
 ******************************************************************************/
 
#ifndef ALGO_SKIP_LIST_H__
#define ALGO_SKIP_LIST_H__
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <exception>

namespace alg {
	template<typename KeyT, typename ValueT>
	class SkipList {
	private:
		struct SkipNode {
			KeyT	key;			// key
			ValueT	value;			// value
			SkipNode ** forward;  	// pointers to different levels 
		};

		struct SkipNode * m_header;	// the header node, empty
		int m_level;				// the max level of skip list

		static const int SL_MAX_LEVEL = 6;

		class NotFoundException: public std::exception {
			public:
			virtual const char * what() const throw() {
				return "cannot find the element in skiplist";
			}
		} excp_notfound;

	public:
		SkipList() {
			m_header = make_node(SL_MAX_LEVEL, 0, 0);
			m_level = 0;
		}

		~SkipList() {	
			// TODO: free nodes
		}

	private:
		SkipList(const SkipList &);
		SkipList& operator=(const SkipList &);
		
	public:
		/**
		 * search the given key from the skip list
		 * if the key is not exist, throw exception
		 */
		inline ValueT operator[] (KeyT key) const {
			struct SkipNode* x = m_header;

			// travels down until level-0
			for(int i = m_level; i >= 0; i--) {
				while(x->forward[i] != NULL && x->forward[i]->key < key) {
					x = x->forward[i];
				}
			}
			x = x->forward[0];
			if(x != NULL && x->key == key)
				return x->value;
			throw excp_notfound;
		}

		/**
		 * insert a key->key pair into the list
		 */
		void insert(KeyT key, ValueT value) {
			struct SkipNode * x = m_header;	
			struct SkipNode * update[SL_MAX_LEVEL + 1];
			memset(update, 0, SL_MAX_LEVEL + 1);

			// travels down the list until we found a proper node
			for(int i = m_level; i >= 0; i--) {
				while(x->forward[i] != NULL && x->forward[i]->key < key) {
					x = x->forward[i];
				}
				update[i] = x; 
			}
			x = x->forward[0];

			// if it's not the largest key or duplicated key (middle ones)
			if(x == NULL || x->key != key) {        
				int lvl = random_level();	// random promotion

				// for nodes higher than  current max level
				// make 'header node' as it's prev
				if(lvl > m_level) {
					for(int i = m_level + 1; i <= lvl; i++) {
						update[i] = m_header;
					}
					m_level = lvl;
				}
				x = make_node(lvl, key, value);
				
				// for each node travlling down, relink into the skiplist
				for(int i = 0; i <= lvl; i++) {
					x->forward[i] = update[i]->forward[i];
					update[i]->forward[i] = x;
				}
			}
		}

		/**
		 * delete a node by it's key
		 */
		void delete_key(KeyT key) {
			struct SkipNode* x = m_header;	
			struct SkipNode* update[SL_MAX_LEVEL + 1];
			memset(update, 0, SL_MAX_LEVEL + 1);

			// find the node, and record it's level update info
			for(int i = m_level; i >= 0; i--) {
				while(x->forward[i] != NULL && x->forward[i]->key < key) {
					x = x->forward[i];
				}
				update[i] = x; 
			}
			x = x->forward[0];

			// delete every level's key
			if(x != NULL && x->key == key) {
				for(int i = 0; i <= m_level; i++) {
					if(update[i]->forward[i] != x)
						break;
					update[i]->forward[i] = x->forward[i];
				}
				free(x);

				while(m_level > 0 && m_header->forward[m_level] == NULL) {
					m_level--;
				}
			}
		}

		void print() {
			for(int i=m_level-1;i>=0;i--) {
				SkipNode* x = m_header->forward[i];
				printf("{");
				while(x != NULL) {
					printf("%d->%d", x->key, x->value);
					x = x->forward[i];
					if(x != NULL)
						printf(", ");
				}    
				printf("}\n");
			}
		}
	private:
		/**
		 * normalize to [0.0 1.0]
		 */
		inline float rand_norm() { return (float) rand() / RAND_MAX; }
	
		/**
		 * get the random promote level 
		 */
		int random_level() {
			int lvl = 0;
			// the possibility is 1/2 for each level	
			while(rand_norm() < 0.5f && lvl < SL_MAX_LEVEL)
			lvl++;

			return lvl;
		} 

		/**
		 * make a node with specified level & key
		 */
		SkipNode * make_node(int level, KeyT key, ValueT value) {
			SkipNode * n = new SkipNode;

			// the max forward entry for a key is : level + 1
			n->forward = new struct SkipNode *[level + 1];
			n->key = key;
			n->value = value;

			return n;
		}
	};
}

#endif //
