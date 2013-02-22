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
 
#ifndef __SKIP_LIST_H__
#define __SKIP_LIST_H__
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define SL_MAX_LEVEL 6

struct SkipNode {
	int32_t key;
	int32_t value;
	struct SkipNode ** forward;  // pointers to different levels 
};

struct SkipSet {
	struct SkipNode * header;
	int level;
};

/**
 * normalize to [0.0 1.0]
 */
#define RAND_NORM() ((float) rand() / RAND_MAX)

/**
 * get the random promote level 
 */
static inline int 
__sl_random_level() {
    int lvl = 0;
	// the possibility is 1/2 for each level	
    while(RAND_NORM() < 0.5f && lvl < SL_MAX_LEVEL)
	lvl++;

    return lvl;
} 

/**
 * make a node with specified level & key
 */
static inline struct SkipNode * __sl_make_node(int level, int key, int value) {
    struct SkipNode * n = (struct SkipNode *)malloc(sizeof(struct SkipNode));

	// the max forward entry for a key is : level + 1
    n->forward = (struct SkipNode **)calloc(level + 1, sizeof(struct SkipNode *));
    n->key = key;
	n->value = value;

    return n;
}

static inline struct SkipSet * 
sl_make_skipset() {
    struct SkipSet * ss = (struct SkipSet*)malloc(sizeof(struct SkipSet));
    ss->header = __sl_make_node(SL_MAX_LEVEL, 0, 0);
    ss->level = 0;
    return ss;
}

/**
 * search the given key from the skip list
 * if the key is not exist, return INT_MIN
 */
static inline int32_t 
sl_get(const struct SkipSet* ss, int key) 
{
    int i;
    struct SkipNode* x = ss->header;
	
	// travels down until level-0
    for(i = ss->level; i >= 0; i--) {
        while(x->forward[i] != NULL && x->forward[i]->key < key) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if(x != NULL && x->key == key)
        return x->value;
    return INT_MIN;
}

/**
 * insert a key->key pair into the list
 */
static inline void 
sl_insert(struct SkipSet * ss, int32_t key, int32_t value) {
    int i;
    struct SkipNode * x = ss->header;	
    struct SkipNode * update[SL_MAX_LEVEL + 1];
    memset(update, 0, SL_MAX_LEVEL + 1);

	// travels down the list until we found a proper node
    for(i = ss->level; i >= 0; i--) {
        while(x->forward[i] != NULL && x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x; 
    }
    x = x->forward[0];

	// if it's not the largest key or duplicated key (middle ones)
    if(x == NULL || x->key != key) {        
        int lvl = __sl_random_level();	// random promotion
 
		// for nodes higer than  current max level
		// make 'header node' as it's prev
		if(lvl > ss->level) {
			for(i = ss->level + 1; i <= lvl; i++) {
				update[i] = ss->header;
			}
			ss->level = lvl;
		}
        x = __sl_make_node(lvl, key, value);
		
		// for each node travlling down, relink into the skiplist
		for(i = 0; i <= lvl; i++) {
			x->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = x;
		}
    }
}

/**
 * delete a node by it's key
 */
static inline void 
sl_delete(struct SkipSet* ss, int key) {
    int i;
    struct SkipNode* x = ss->header;	
    struct SkipNode* update[SL_MAX_LEVEL + 1];
    memset(update, 0, SL_MAX_LEVEL + 1);

	// find the node, and record it's level update info
    for(i = ss->level; i >= 0; i--) {
        while(x->forward[i] != NULL && x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x; 
    }
    x = x->forward[0];

	// delete every level's key
    if(x != NULL && x->key == key) {
		for(i = 0; i <= ss->level; i++) {
			if(update[i]->forward[i] != x)
				break;
			update[i]->forward[i] = x->forward[i];
		}
		free(x);

		while(ss->level > 0 && ss->header->forward[ss->level] == NULL) {
			ss->level--;
		}
    }
}

#endif //
