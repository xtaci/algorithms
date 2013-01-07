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
			skip_list_demo

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

clean:
	rm $(PROGRAMS)
