#include <stdio.h>
#include <stdlib.h>

#include "double_linked_list.h"
#include "sol.h"

using namespace alg;

struct DemoNode{
	int key;
	struct list_head list;
};

int main()
{
	struct list_head head, head2;
	INIT_LIST_HEAD(&head);
	INIT_LIST_HEAD(&head2);

	printf("list_add[head#1]:\n");
	int i;
	struct DemoNode * node; 

	for(i = 0; i< 10; i++) {
		node = (struct DemoNode *)malloc(sizeof(struct DemoNode));
		node->key = i;
		list_add(&node->list, &head);
		printf("%d\n", i);
	}

	
	printf("list_add[head#2]:\n");
	for(i = 10; i< 20; i++) {
		node = (struct DemoNode *)malloc(sizeof(struct DemoNode));
		node->key = i;
		list_add(&node->list, &head2);
		printf("%d\n", i);
	}

	// iterate 
	printf("list_for_each:\n");
	struct list_head *pos;
	list_for_each(pos, &head){
		struct DemoNode * node = list_entry(pos, struct DemoNode, list);
		printf("%d\n", node->key);
	}

	printf("list_for_each_prev:\n");
	list_for_each_prev(pos, &head){
		struct DemoNode * node = list_entry(pos, struct DemoNode, list);
		printf("%d\n", node->key);
	}
	
	printf("list_for_each_entry:\n");
	list_for_each_entry(node, &head, list){
		printf("%d\n", node->key);
	}
	
	// mtf & mao
	printf("list_mtf: move the 2nd element to 1st pos:\n");
	list_mtf(head.next->next, &head);  // 2nd element
	list_for_each_entry(node, &head, list){
		printf("%d\n", node->key);
	}

	printf("list_mao: move ahead the 3rd element one pos:\n");
	list_mao(head.next->next->next, &head); // 3rd element
	list_for_each_entry(node, &head, list){
		printf("%d\n", node->key);
	}

	// move 
	printf("list_move: move an element to another list\n");
	list_move(head.next, &head2);
	printf("head#1:\n");
	list_for_each_entry(node, &head, list){
		printf("%d\n", node->key);
	}

	printf("head#2:\n");
	list_for_each_entry(node, &head2, list){
		printf("%d\n", node->key);
	}

	//splice
	printf("list_splice:\n");
	list_splice_init(&head, &head2);
	list_for_each_entry(node, &head2, list){
		printf("%d\n", node->key);
	}
	
	// delete all nodes
	printf("list_for_each_entry_safe to delete everything:\n");
	struct DemoNode * n;
	list_for_each_entry_safe(node, n, &head, list){
		list_del(&node->list);
		printf("freeing %d\n", node->key);
		free(node);
	}

	list_for_each_entry_safe(node, n, &head2, list){
		list_del(&node->list);
		printf("freeing %d\n", node->key);
		free(node);
	}
	return 0;
}
