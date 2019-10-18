/*******************************************************************************
* Segment tree or segtree is a basically a binary tree used for storing the intervals or segments. Each node in the segment tree represents an interval.
* Consider an array A of size N and a corresponding segtree T:
*
* 1)The root of T will represent the whole array A[0:N-1].
* 2)Each leaf in the segtree T will represent a single element A[i] such that 0 <= i < N.
* 3) The internal nodes in the segtree tree T represent union of elementary intervals A[i:j] where 0 <= i < j < N.
*
*
* This implementation has a Segment tree which does a Range Sum query using Lazy Propogation
******************************************************************************/

#ifndef ALGO_SEGMENT_H_
#define ALGO_SEGMENT_H_

#include<vector>

class Segment {
    vector<int> Tree;
    vector<int> inputArray;
    vector<int> lazyArray;

public:
    Segment(vector<int> inputArray) {
        this->inputArray = inputArray;
        Tree.assign(2 * n + 1, 0);
        lazyArray.assign(2 * n + 1, 0);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            // Leaf node will have a single element
            tree[node] = A[start];
        } else {
            int mid = (start + end) / 2;
            // Recurse on the left child
            build(2 * node, start, mid);
            // Recurse on the right child
            build(2 * node + 1, mid + 1, end);
            // Internal node will have the sum of both of its children
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void updateRange(int node, int start, int end, int l, int r, int val) {
        // out of range
        if (start > end or start > r or end < l)
            return;

        // Current node is a leaf node
        if (start == end) {
            // Add the difference to current node
            tree[node] += val;
            return;
        }

        // If not a leaf node, recur for children.
        int mid = (start + end) / 2;
        updateRange(node * 2, start, mid, l, r, val);
        updateRange(node * 2 + 1, mid + 1, end, l, r, val);

        // Use the result of children calls to update this node
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void updateRange(int node, int start, int end, int l, int r, int val) {
        if (lazy[node] != 0) {
            // This node needs to be updated
            tree[node] += (end - start + 1) * lazy[node];    // Update it
            if (start != end) {
                lazy[node * 2] += lazy[node];                  // Mark child as lazy
                lazy[node * 2 + 1] += lazy[node];                // Mark child as lazy
            }
            lazy[node] = 0;                                  // Reset it
        }
        if (start > end or start > r or end < l)              // Current segment is not within range [l, r]
            return;
        if (start >= l and end <= r) {
            // Segment is fully within range
            tree[node] += (end - start + 1) * val;
            if (start != end) {
                // Not leaf node
                lazy[node * 2] += val;
                lazy[node * 2 + 1] += val;
            }
            return;
        }
        int mid = (start + end) / 2;
        updateRange(node * 2, start, mid, l, r, val);        // Updating left child
        updateRange(node * 2 + 1, mid + 1, end, l, r, val);   // Updating right child
        tree[node] = tree[node * 2] + tree[node * 2 + 1];        // Updating root with max value
    }

    int queryRange(int node, int start, int end, int l, int r) {
        if (start > end or start > r or end < l)
            return 0;         // Out of range
        if (lazy[node] != 0) {
            // This node needs to be updated
            tree[node] += (end - start + 1) * lazy[node];            // Update it
            if (start != end) {
                lazy[node * 2] += lazy[node];         // Mark child as lazy
                lazy[node * 2 + 1] += lazy[node];    // Mark child as lazy
            }
            lazy[node] = 0;                 // Reset it
        }
        if (start >= l and end <= r)             // Current segment is totally within range [l, r]
            return tree[node];
        int mid = (start + end) / 2;
        int p1 = queryRange(node * 2, start, mid, l, r);         // Query left child
        int p2 = queryRange(node * 2 + 1, mid + 1, end, l, r); // Query right child
        return (p1 + p2);
    }
};

#endif
