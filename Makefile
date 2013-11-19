.PHONY: all clean
CC=gcc
CPP=g++
AR=ar
RANLIB=ranlib
CFLAGS= -g -O2 -Wall -Wno-unused-function
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
			sort_demo

all: $(PROGRAMS)

%: $(SRCDIR)/%.cpp $(DEPS)
	$(CPP) $(CFLAGS) -o $@ $< $(INCLUDEDIR) $(LIBS)

clean:
	rm -rf $(PROGRAMS) *.dSYM
