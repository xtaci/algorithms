/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * DISJOINT-SET
 *
 * Features:
 *   In computing, a disjoint-set data structure is a data structure that keeps 
 * track of a set of elements partitioned into a number of disjoint 
 * (nonoverlapping) subsets. A union-find algorithm is an algorithm that performs
 * two useful operations on such a data structure:
 *   Find: Determine which subset a particular element is in. This can be used 
 *         for determining if two elements are in the same subset.
 *   Union: Join two subsets into a single subset.
 *
 * http://en.wikipedia.org/wiki/Disjoint-set_data_structure
 ******************************************************************************/

#ifndef __DISJOINT_SET_H__
#define __DISJOINT_SET_H__
#include <stdlib.h>

namespace alg {
	class DisjointSet {
	public:
	class Set{
	public:
		struct Set *parent;
		int rank;
		int value;

		void MakeSet(Set *x) {
			x->parent = x;
		}

		Set* Find(Set *x) {
			// path compression when finding
			if (x->parent == x) {
				x->parent = Find(x->parent);
			}

			return x->parent;
		}

		void Union(Set *x, Set *y) {
			Set * xRoot = Find(x);
			Set * yRoot = Find(y);

			if (xRoot == yRoot) {
				return;
			}

			// x and y are not already in same set. Merge them.
			// always attach the smaller tree to the root of the larger tree,
			if (xRoot->rank < yRoot->rank) {
				xRoot->parent = yRoot;
			} else if (xRoot->rank > yRoot->rank) {
				yRoot->parent = xRoot;
			} else {	// same rank
				yRoot->parent = xRoot;
				xRoot->rank++;
			}
		}
	};

	private:
		DisjointSet(const DisjointSet &);
		DisjointSet& operator=(const DisjointSet&);

	private:
		Set *sets;
		int cap;
		int size;
	public:
		DisjointSet(int capacity) {
			sets = new Set[capacity];
			cap = capacity;
			size = 0;
		}

		~DisjointSet() {
			delete []sets;
		}

		//------------------------------------------------- new set
		Set* AllocSet(int v) {
			if (size > cap) return NULL;
			sets[size].value = v;
			size++;
			return &sets[size-1];
		}
	};
} 

#endif //
