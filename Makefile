.PHONY: all clean
CC=gcc
CPP=g++
CFLAGS=-g -Wall
SRCDIR = ./src
INCLUDEDIR = ./include
DEPS = $(INCLUDEDIR)/${wildcard *.h}
PROGRAMS =	insertion_sort_demo \
			radix_sort_demo \
			shuffle_demo \
			quick_sort_demo \
			random_select_demo \
			prime_sieve_eratosthenes \
			hash_multi_demo \
			hash_table_demo \
			double_linked_list_demo \
			stack_demo \
			queue_demo \
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
			graph_demo \
			prim_mst_demo \
			directed_graph_demo \
			dijkstra_demo 	\
			bellman_ford_demo \
			graph_search_demo
			

all: $(PROGRAMS)

heap_demo: $(SRCDIR)/heap_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

insertion_sort_demo: $(SRCDIR)/insertion_sort_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

radix_sort_demo: $(SRCDIR)/radix_sort_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

shuffle_demo: $(SRCDIR)/shuffle_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

quick_sort_demo: $(SRCDIR)/quick_sort_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

random_select_demo: $(SRCDIR)/random_select_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

prime_sieve_eratosthenes: $(SRCDIR)/prime_sieve_eratosthenes.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) -lm

hash_multi_demo: $(SRCDIR)/hash_multi_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) -lm

hash_table_demo: $(SRCDIR)/hash_table_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) -lm

double_linked_list_demo: $(SRCDIR)/double_linked_list_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

stack_demo: $(SRCDIR)/stack_demo.c $(DEPS)
	$(CPP) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

queue_demo: $(SRCDIR)/queue_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

prime_test: $(SRCDIR)/prime_test.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

universal_hash_demo: $(SRCDIR)/universal_hash_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

perfect_hash_demo: $(SRCDIR)/perfect_hash_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

binary_search_tree_demo: $(SRCDIR)/binary_search_tree_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

rbtree_demo: $(SRCDIR)/rbtree_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

interval_tree_demo: $(SRCDIR)/interval_tree_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

dos_tree_demo: $(SRCDIR)/dos_tree_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

skip_list_demo: $(SRCDIR)/skip_list_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

lcs_demo: $(SRCDIR)/lcs_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

graph_demo: $(SRCDIR)/graph_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

prim_mst_demo: $(SRCDIR)/prim_mst_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

directed_graph_demo: $(SRCDIR)/directed_graph_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

dijkstra_demo: $(SRCDIR)/dijkstra_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

bellman_ford_demo: $(SRCDIR)/bellman_ford_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR)

graph_search_demo: $(SRCDIR)/graph_search_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) -lm

clean:
	rm $(PROGRAMS)
