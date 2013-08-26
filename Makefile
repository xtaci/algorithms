.PHONY: all clean
CC=gcc
CPP=g++
AR=ar
RANLIB=ranlib
CFLAGS= -O2 -Wall -Wno-unused-function
SRCDIR = ./src
INCLUDEDIR = -I./include -I.
DEPS = 
LIBS = -lm
PROGRAMS =  m_based \
			integer_demo \
			insertion_sort_demo \
			radix_sort_demo \
			shuffle_demo \
			quick_sort_demo \
			merge_sort_demo \
			random_select_demo \
			hash_multi_demo \
			hash_table_demo \
			double_linked_list_demo \
			stack_demo \
			queue_demo \
			priority_queue_demo \
			prime_test \
			universal_hash_demo \
			perfect_hash_demo \
			binary_search_tree_demo \
			rbtree_demo \
			heap_demo \
			interval_tree_demo \
			dos_tree_demo \
			skip_list_demo \
			lcs_demo	\
			prim_mst_demo \
			directed_graph_demo \
			undirected_graph_demo \
			dijkstra_demo 	\
			bellman_ford_demo \
			graph_search_demo \
			edmonds_karp_demo \
			astar_demo	\
			hash_string_demo \
			bitset_demo	\
			bloom_filter_demo \
			sha1_demo	\
			huffman_demo \
			word_seg_demo \
			md5_demo \
			trie_demo \
			simhash_demo \
			imath_demo \
			random_demo \
			k-means_demo \
			kmp_demo \
			heap_sort_demo \
			kruskal_mst_demo

all: $(PROGRAMS)

%: $(SRCDIR)/%.cpp $(DEPS)
	$(CPP) $(CFLAGS) -o $@ $< $(INCLUDEDIR) $(LIBS)

clean:
	rm -rf $(PROGRAMS) *.dSYM
