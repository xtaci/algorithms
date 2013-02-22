/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * GENERIC HASH TABLE 
 *
 * Features:
 * 1. separate chaining for resolving collisions
 * 
 * http://en.wikipedia.org/wiki/Hash_table
 *
 ******************************************************************************/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdint.h>
#include <limits.h>
#include "double_linked_list.h"
#include "hash_multi.h"

/**
 * definiton of Key-Value pair.
 */
struct HashKV {
	uint32_t key;	// 32-bit key
	uintptr_t value;	// value can be used as a pointer.
	struct list_head node;	// KV is a list element.
};

/**
 * define a Hash slot, a hash slot contains arbitary HashKV (key-value pair),
 * depending on hash collision.
 * we use a list structure to represent the slot.
 */
typedef struct list_head HashSlot;

/**
 * definition of a hash table.
 */
struct HashTable {
	uint32_t size;		// the size of the hash table.
	HashSlot * slots;	// all of the slots
	struct MultiHash * multi;	// the hash function parameter.
};

/**
 * create a hash table with size -- 'num_elements' .
 */
static inline struct HashTable * 
hash_table_create(uint32_t num_elements)
{
	struct HashTable * ht = (struct HashTable *)malloc(sizeof(struct HashTable));
	// init multiplication hash function
	ht->multi = multi_hash_init(num_elements);
	ht->size = MULTI_HASH_TABLE_SIZE(ht->multi);
	ht->slots = (HashSlot *)malloc(sizeof(HashSlot) * ht->size);

	int i;
	for (i=0; i<ht->size; i++) {
		INIT_LIST_HEAD(&ht->slots[i]);
	}

	return ht;
}

/**
 * add a key-value pair to the hash table. 
 */
static inline void 
hash_table_set(struct HashTable * ht, uint32_t key, uintptr_t value)
{
	// hash the key using a hash function.
	uint32_t hash = multi_hash(ht->multi, key);

	//  we iterate through the list.
	struct HashKV * kv;
	list_for_each_entry(kv, &ht->slots[hash], node){
		if (kv->key == key) {	// ok, found in the list.
			kv->value = value;
			return;
		}
	}

	// reaching here means a new key is given,
	// create a new HashKV struct for it.
	kv = (struct HashKV *)malloc(sizeof(struct HashKV));	
	kv->key = key;
	kv->value = value;
	
	list_add(&kv->node, &ht->slots[hash]);
}

/**
 * get a value with given 'key'
 * returns 0 when the 'key' in not in the table.
 */
static inline uintptr_t 
hash_table_get(struct HashTable * ht, uint32_t key)
{
	uint32_t hash = multi_hash(ht->multi, key);

	// iterate through the list
	struct HashKV * kv;
	list_for_each_entry(kv, &ht->slots[hash], node){
		if (kv->key == key) {	// ok, we found it.
			return kv->value;
		}
	}

	return 0;
}

/**
 * destroy the hash table, free spaces.
 */
static inline void 
hash_table_destroy(struct HashTable * ht)
{
	if (ht==NULL) return;
	free(ht->multi);

	struct HashKV * kv, *nkv;
	int i;
	for (i=0;i<ht->size;i++) {
		list_for_each_entry_safe(kv,nkv,&ht->slots[i], node){
			list_del(&kv->node);
			free(kv);
		}
	}

	free(ht->slots);
	free(ht);
}

#endif //
