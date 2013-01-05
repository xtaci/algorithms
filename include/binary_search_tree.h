/*******************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Binary Search Tree
 * Features:
 * 1. Expected search time is O(nlogn).
 * 2. Data should be !!!SHUFFLED!!! first before tree creation.
 * 3. First initialize the value of the root (pointer to the 
      structure treeNode) with NULL. eg:
      treeNode *root = NULL
 *******************************************/

#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include <stdlib.h>
#include <stdint.h>

typedef struct treeNode
{
	int32_t data;
	struct treeNode *left;
	struct treeNode *right;

}treeNode;

/**
 * search he minimal element in the binary search tree.
 */
inline treeNode * bst_find_min(treeNode *node)
{
	if(node==NULL)
	{
		/* There is no element in the tree */
		return NULL;
	}
	if(node->left) /* Go to the left sub tree to find the min element */
		return bst_find_min(node->left);
	else 
		return node;
}

/**
 * search the maximal element in the binary search tree.
 */
inline treeNode * bst_find_max(treeNode *node)
{
	if(node==NULL)
	{
		/* There is no element in the tree */
		return NULL;
	}
	if(node->right) /* Go to the left sub tree to find the min element */
		bst_find_max(node->right);
	else 
		return node;
}

/**
 * insert a new data into the binary search tree.
 */
inline treeNode * bst_insert(treeNode *node,int data)
{
	if (node==NULL)
	{
		treeNode *temp;
		temp = (treeNode *)malloc(sizeof(treeNode));
		temp -> data = data;
		temp -> left = temp -> right = NULL;
		return temp;
	}

	if(data >(node->data))
	{
		node->right = bst_insert(node->right,data);
	}
	else if(data < (node->data))
	{
		node->left = bst_insert(node->left,data);
	}
	/* Else there is nothing to do as the data is already in the tree. */
	return node;
}

#endif //
