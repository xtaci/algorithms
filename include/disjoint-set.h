/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * Disjoint-set data structure
 *
 *   In computing, a disjoint-set data structure is a data structure that keeps 
 * track of a set of elements partitioned into a number of disjoint (nonoverlapping)
 * subsets. A union-find algorithm is an algorithm that performs two useful 
 * operations on such a data structure:
 * Find: Determine which subset a particular element is in. This can be used 
 *		for determining if two elements are in the same subset.
 * Union: Join two subsets into a single subset.
 *
 * http://en.wikipedia.org/wiki/Disjoint-set_data_structure
 ******************************************************************************/

#ifndef ALGO_DISJOINTSET_H__
#define ALGO_DISJOINTSET_H__

namespace alg {
	template<typename T>
		struct Set{
			Set<T>* parent;
			int rank;
		};

	template<typename T>
		void MakeSet(T *s){
			s->parent = s;
			s->rank = 0;
		}

	template<typename T>
		void Union(T *x, T *y) {
			Link(FindSet(x), FindSet(y));
		}

	template<typename T>
		void Link(T *x, T *y) {
			if (x->rank > y->rank) {
				y->parent = x;
			} else {
				x->parent = y;
				if (x->rank == y->rank) {
					y->rank +=1;
				}
			}
		}

	template<typename T>
		T* FindSet(T *x) {
			if (x != x->parent) {
				x->parent = FindSet(x->parent);
			}

			return x->parent;
		}
}

#endif //
