/*
 * Segment tree is a data structure.
 * It can handle operations and queries in ranges.
 * Each operation or query on it has a complexity of O(log n).
 *
 * This segment tree provides:
 *		1. Add a number to all numbers in a range;
 *		2. Multiplying a number to all numbers in a range;
 *		3. Calculate the sum of all numbers in a range.
 */

#ifndef ALGO_SEGMENT_TREE__H__
#define ALGO_SEGMENT_TREE__H__
#include <iostream>
#include <algorithm>

namespace alg {
	
	class SegmentTree {
	private:
		static const int MAXSIZE = 10000;
		
		int a[MAXSIZE], plus[MAXSIZE * 4], mul[MAXSIZE * 4], siz;
	
		inline int l(int x) { return x << 1; }
		inline int r(int x) { return x << 1 | 1; }
		void push_down(int b, int e, int x) {
			int mid = b + e >> 1;
			a[l(x)] = a[l(x)] * mul[x] + plus[x] * (mid - b + 1);
			a[r(x)] = a[r(x)] * mul[x] + plus[x] * (e - mid);
			mul[l(x)] = mul[l(x)] * mul[x];
			mul[r(x)] = mul[r(x)] * mul[x];
			plus[l(x)] = plus[l(x)] * mul[x] + plus[x];
			plus[r(x)] = plus[r(x)] * mul[x] + plus[x];
			mul[x] = 1;
			plus[x] = 0;
		}
	
	public:
		int size() const { return siz; }
		
		int build(int* source, int sz, int x = 1, int b = 1, int e = -1) {
			if (e == -1)
				siz = e = sz;
			mul[x] = 1;
			int mid = b + e >> 1;
			if (b == e)
				return a[x] = source[b];
			else
			return a[x] = build(source, sz, l(x), b, mid) + build(source, sz, r(x), mid + 1, e);
		}
		
		void multiply(int b_, int e_, int d, int x = 1, int b = 1, int e = -1) {
			if (e == -1)
				e = siz;
			if (e_ < b || e < b_)
				return;
			if (b_ <= b && e <= e_) {
				mul[x] *= d;
				plus[x] *= d;
				a[x] *= d;
			} else {
				int mid = b + e >> 1;
				push_down(b, e, x);
				multiply(b_, e_, d, l(x), b, mid);
				multiply(b_, e_, d, r(x), mid + 1, e);
				a[x] = a[l(x)] + a[r(x)];
			}
		}
		
		void add(int b_, int e_, int d, int x = 1, int b = 1, int e = -1) {
			if (e == -1)
				e = siz;
			if (e_ < b || e < b_)
				return;
			if (b_ <= b && e <= e_) {
				plus[x] += d;
				a[x] += (e - b + 1) * d;
			} else {
				int mid = b + e >> 1;
				push_down(b, e, x);
				add(b_, e_, d, l(x), b, mid);
				add(b_, e_, d, r(x), mid + 1, e);
				a[x] = a[l(x)] + a[r(x)];
			}
		}
		
		int query(int b_, int e_, int x = 1, int b = 1, int e = -1) {
			if (e == -1)
				e = siz;
			if (e_ < b || e < b_)
				return 0;
			if (b_ <= b && e <= e_)
				return a[x];
			int mid = b + e >> 1;
			push_down(b, e, x);
			return query(b_, e_, l(x), b, mid) + query(b_, e_, r(x), mid + 1, e);
		}
		
		SegmentTree(): siz(0) { }
		SegmentTree(int* source, int sz) { build(source, sz); } 
	};
	
}

#endif //ALGO_SEGMENT_TREE__H__
