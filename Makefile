.PHONY: all clean
CC=clang
CPP=clang++
AR=ar
RANLIB=ranlib
CFLAGS= -g -Wall -Wno-unused-function
C11FLAGS= -g -Wall -Wno-unused-function -std=c++11
SRCDIR = ./src
INCLUDEDIR = -I./include -I.
DEPS = 
LIBS = -lm

PROGRAMS = m_based_demo \
			integer_demo \
       		insertion_sort_demo \
					shell_sort_demo \
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
			universal_hash_demo \
			perfect_hash_demo \
			binary_search_tree_demo \
			rbtree_demo \
			heap_demo \
			interval_tree_demo \
			dos_tree_demo \
			skiplist_demo \
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
			LRU_cache_demo \
			base64_demo	\
			max_subarray_demo \
			disjoint-set_demo \
			relabel_to_front_demo \
			btree_demo \
			sort_demo \
			fib-heap_demo \
			scc_demo \
			sort_demo \
			bubble_sort_demo \
			selection_sort_demo	\
			8queue_demo \
			palindrome_demo \
			suffix_tree_demo \
			avl_demo

all: $(PROGRAMS)

m_based_demo: $(SRCDIR)/m_based_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

integer_demo: $(SRCDIR)/integer_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

insertion_sort_demo: $(SRCDIR)/insertion_sort_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

shell_sort_demo: $(SRCDIR)/shell_sort_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

radix_sort_demo: $(SRCDIR)/radix_sort_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

shuffle_demo: $(SRCDIR)/shuffle_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

quick_sort_demo: $(SRCDIR)/quick_sort_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

merge_sort_demo: $(SRCDIR)/merge_sort_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

random_select_demo: $(SRCDIR)/random_select_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

hash_multi_demo: $(SRCDIR)/hash_multi_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

hash_table_demo: $(SRCDIR)/hash_table_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

double_linked_list_demo: $(SRCDIR)/double_linked_list_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

stack_demo: $(SRCDIR)/stack_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

queue_demo: $(SRCDIR)/queue_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

priority_queue_demo: $(SRCDIR)/priority_queue_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

prime_demo: $(SRCDIR)/prime_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

universal_hash_demo: $(SRCDIR)/universal_hash_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

perfect_hash_demo: $(SRCDIR)/perfect_hash_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

binary_search_tree_demo: $(SRCDIR)/binary_search_tree_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

rbtree_demo: $(SRCDIR)/rbtree_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

heap_demo: $(SRCDIR)/heap_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

interval_tree_demo: $(SRCDIR)/interval_tree_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

dos_tree_demo: $(SRCDIR)/dos_tree_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

skiplist_demo: $(SRCDIR)/skiplist_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

lcs_demo: $(SRCDIR)/lcs_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

prim_mst_demo: $(SRCDIR)/prim_mst_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

directed_graph_demo: $(SRCDIR)/directed_graph_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

undirected_graph_demo: $(SRCDIR)/undirected_graph_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

dijkstra_demo: $(SRCDIR)/dijkstra_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

bellman_ford_demo: $(SRCDIR)/bellman_ford_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

graph_search_demo: $(SRCDIR)/graph_search_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

edmonds_karp_demo: $(SRCDIR)/edmonds_karp_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

astar_demo: $(SRCDIR)/astar_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

hash_string_demo: $(SRCDIR)/hash_string_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

bitset_demo: $(SRCDIR)/bitset_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

bloom_filter_demo: $(SRCDIR)/bloom_filter_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

sha1_demo: $(SRCDIR)/sha1_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

huffman_demo: $(SRCDIR)/huffman_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

word_seg_demo: $(SRCDIR)/word_seg_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

md5_demo: $(SRCDIR)/md5_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

trie_demo: $(SRCDIR)/trie_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

simhash_demo: $(SRCDIR)/simhash_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

imath_demo: $(SRCDIR)/imath_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

random_demo: $(SRCDIR)/random_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

k-means_demo: $(SRCDIR)/k-means_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

kmp_demo : $(SRCDIR)/kmp_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

kruskal_mst_demo: $(SRCDIR)/kruskal_mst_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

LRU_cache_demo: $(SRCDIR)/LRU_cache_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

base64_demo: $(SRCDIR)/base64_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

max_subarray_demo: $(SRCDIR)/max_subarray_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

disjoint-set_demo: $(SRCDIR)/disjoint-set_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

relabel_to_front_demo: $(SRCDIR)/relabel_to_front_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

btree_demo: $(SRCDIR)/btree_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

sort_demo: $(SRCDIR)/sort_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

fib-heap_demo: $(SRCDIR)/fib-heap_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

scc_demo: $(SRCDIR)/scc_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

bubble_sort_demo: $(SRCDIR)/bubble_sort_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

selection_sort_demo: $(SRCDIR)/selection_sort_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

8queue_demo: $(SRCDIR)/8queue_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

palindrome_demo: $(SRCDIR)/palindrome_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

suffix_tree_demo: $(SRCDIR)/suffix_tree_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

avl_demo: $(SRCDIR)/avl_demo.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

suffix_array_demo: $(SRCDIR)/suffix_array_demo.cpp
	$(CPP) $(C11FLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

clean:
	rm -rf $(PROGRAMS) *.dSYM

