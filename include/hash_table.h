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
#include <stdexcept>
#include "double_linked_list.h"
#include "hash_multi.h"

namespace alg {
	/**
	 * definition of a hash table.
	 */
	template<typename T>
		class HashTable {
			private:
				/**
				 * definiton of Key-Value pair.
				 */
				struct HashKV {
					uint32_t key;	// 32-bit key
					T value;		// value
					struct list_head node;	// KV is a list element.
				};

			private:
				uint32_t m_size;			// the size of the hash table.
				struct list_head * m_slots;	// all of the slots, each slot is an linked-list
				struct MultiHash * m_multi;	// the hash function parameter.

			public:
				/**
				 * create a hash table with max size .
				 */
				HashTable(uint32_t max) {
					// init multiplication hash function
					m_multi = multi_hash_init(max);
					m_size = multi_hash_table_size(m_multi);
					m_slots = new list_head[m_size];

					for (uint32_t i=0; i<m_size; i++) {
						INIT_LIST_HEAD(&m_slots[i]);
					}
				}

				~HashTable() {
					for (uint32_t i=0;i<m_size;i++) {
						HashKV * kv, *nkv;
						list_for_each_entry_safe(kv,nkv,&m_slots[i], node){
							list_del(&kv->node);
							delete kv;
						}
					}

					delete m_multi;
					delete [] m_slots;
				}
			private:
				HashTable(const HashTable &);
				HashTable& operator=(const HashTable &);
			public:

				/**
				 * test if the hash table has the key
				 */
				bool contains(uint32_t key) const {
					// hash the key using a hash function.
					uint32_t hash = multi_hash(m_multi, key);

					//  we iterate through the list.
					HashKV * kv;
					list_for_each_entry(kv, &m_slots[hash], node){
						if (kv->key == key) {	// ok, found in the list.
							return true;
						}
					}
					return false;
				}

				/**
				 * delete by key
				 */
				bool delete_key(uint32_t key) {
					// hash the key using a hash function.
					uint32_t hash = multi_hash(m_multi, key);

					HashKV * kv, *nkv;
					list_for_each_entry_safe(kv,nkv,&m_slots[hash], node) {
						if (kv->key == key) {
							list_del(&kv->node);
							delete kv;
							return true;
						}
					}

					return false;
				}

				// const version of operator []
				const T& operator[] (uint32_t key) const {
					// hash the key using a hash function.
					uint32_t hash = multi_hash(m_multi, key);

					//  we iterate through the list.
					HashKV * kv;
					list_for_each_entry(kv, &m_slots[hash], node){
						if (kv->key == key) {	// ok, found in the list.
							return kv->value;
						}
					}

					// reaching here means a new key is given,
					// create a new HashKV struct for it.
					kv = new HashKV;
					kv->key = key;
					list_add(&kv->node, &m_slots[hash]);
					return kv->value;
				}

				/**
				 * operator []
				 */
				T& operator[] (uint32_t key) {
					return const_cast<T&>(static_cast<const HashTable&>(*this)[key]);
				}

				void clear() {
					HashKV * kv, *nkv;
					for (uint32_t i=0;i<m_size;i++) {
						list_for_each_entry_safe(kv,nkv,&m_slots[i], node){
							list_del(&kv->node);
							delete kv;
						}
					}
				}
		};
}

#endif //
