/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * Trie (Prefix tree)
 *
 * http://en.wikipedia.org/wiki/Trie
 ******************************************************************************/

#ifndef ALGO_TRIE_H__
#define ALGO_TRIE_H__
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

namespace alg {
	const int NUMWORD = 26;
	class Trie {
		private:
			class node {
				public:
					int words;
					int prefixes;
					node *edges[NUMWORD];
					node():words(0),prefixes(0) {
						memset(edges, 0, sizeof(edges));
					}
					~node() {
						for (int i=0;i<NUMWORD;i++) {
							if (edges[i] != NULL) {
								delete edges[i];
							}
						}
					}
			};
			node *m_root;
		public:
			Trie() {
				m_root = new node;
			}

			~Trie() {
				delete m_root;
				m_root=NULL;
			}

			void Add(char * str) {
				_lowercase(str);
				_add(m_root, str);
			}

			int Count(const char *str) {
				char * _str = strdup(str);
				_lowercase(_str);

				int cnt = _count(m_root, _str);
				free(_str);
				return cnt;
			}

			int CountPrefix(const char *prefix) {
				char * _str = strdup(prefix);
				_lowercase(_str);

				int cnt = _count_prefix(m_root, _str);
				free(_str);
				return cnt;
			}

		private:
			void _lowercase(char *str) {
				int i;
				for (i=0;str[i];i++) {
					str[i] = tolower(str[i]);
				}
			}

			void _add(node *n, const char * str) {
				if (str[0] == '\0') {
					n->words++;
				} else {
					n->prefixes++;
					int index=str[0]-'a';
					if (n->edges[index]==NULL) {
						n->edges[index] = new node;
					}

					_add(n->edges[index], ++str);
				} 
			}

			int _count(node *n, const char * str) {
				if (str[0] == '\0') {
					return n->words;
				} else {
					int index=str[0]-'a';
					if (n->edges[index]==NULL) {
						return 0;
					}

					return _count(n->edges[index], ++str);
				} 
			}

			int _count_prefix(node *n, char * str) {
				if (str[0] == '\0') {
					return n->prefixes;
				} else {
					int index=str[0]-'a';
					if (n->edges[index]==NULL) {
						return 0;
					}

					return _count_prefix(n->edges[index], ++str);
				} 
			}
	};
}

#endif //
