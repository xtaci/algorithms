/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * SUFFIX ARRAY
 *
 * Features: 
 * suffix array can sort all the suffixs in time complexity O(n*log^2(n)), 
 * and use memory in O(n).  And suffix array can get two suffixs' longest 
 * common prefix(lcp) in O(log(n)) complexity. 
 *
 * You can test it by running suffix_array_demo.cpp
 * Want to get more detailed information about suffix array? 
 *
 * Please google SUFF_AR_ENG.pdf
 *
 * AUTHOR: nowerzt@gmail.com
 ******************************************************************************/

#ifndef ALGO_SUFFIX_ARRAY_H__
#define ALGO_SUFFIX_ARRAY_H__

#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#include <functional>

using namespace std;

namespace alg {
	class SuffixArray {
		private:
			vector<vector<int> > bucket;
			vector<int> suffix;
			int N, L, K;
			const string& str;
			void suffix_sort();
			void update_bucket();

			bool less_than(int a, int b) { 
				if(K==0) return str[a]<str[b];
				else {
					if(bucket[K-1][a]==bucket[K-1][b]) return bucket[K-1][a+L/2]<bucket[K-1][b+L/2];
					else return bucket[K-1][a]<bucket[K-1][b];
				}
			}

			bool equal(int a, int b) {
				return !less_than(a,b) && !less_than(b,a);
			}

		public:
			explicit SuffixArray(const string& s) : N(s.size()), L(0), K(0), str(s) { suffix_sort();}
			// return the sorted suffix
			int operator [] (int i) { return suffix[i];}
			// Given two suffixs of string, return the longest common prefix length
			int lcp_length(int x, int y);
	};

	void SuffixArray::suffix_sort() {
		// init suffix
		suffix.resize(N);
		for(int i=0;i<N;i++) suffix[i]=i;
		// init bucket
		bucket.resize(ceil(log2(N))+1);
		for(size_t k=0;k<bucket.size();k++) bucket[k].resize(N+N);

		for(L=1,K=0;(L>>1)<N;L<<=1,K++) {
			sort(suffix.begin(), suffix.end(), std::bind(&SuffixArray::less_than, *this, placeholders::_1, placeholders::_2));
			update_bucket();
		}
	}


	void SuffixArray::update_bucket() {
		int seq=0;
		bucket[K][suffix[0]]=0;
		for(int i=1;i<N;i++) {
			if(!equal(suffix[i],suffix[i-1])) seq++;
			bucket[K][suffix[i]]=seq;
		}
		fill(bucket[K].begin()+N, bucket[K].end(), -1);
	}

	int SuffixArray::lcp_length(int x, int y) {
		if(x==y) return N-x;
		int ret=0;
		for(int k=K-1;k>=0 && x<N && y<N;k--) {
			if(bucket[k][x]==bucket[k][y]) {
				x += (1<<k);
				y += (1<<k);
				ret += (1<<k);
			}
		}
		return ret;
	}
}

#endif // ALGO_SUFFIX_ARRAY_H__
