#include<iostream>
#include<stdlib.h>
using namespace std;
//STRUCTURE OF A NODE IN A SINGLY LINKED LIST IN C++.
struct node{
	int data;
	struct node *next;
};
//FUNCTION TO INSERT A NODE TO THE EXISTING LINKED LIST OR TO A NEWLY CREATED LINKED LIST.
void push(struct node **head_ref, int data){
	struct node *node;
	node = (struct node*)malloc(sizeof(struct node));
	node->data = data;
	node->next = (*head_ref);          //The nodes which are being inserted to the existing Linked List, they are being inserted from the rear side  
	(*head_ref) = node;                //and every time a node is inserted it is made the head of the linked list.
}
//FUNCTION TO DELETE THE COMPLETE LINKED LIST.
void deletelist(struct node *head_ref){
	struct node *temp;
	struct node *current;
	current = head_ref;
	while(current != NULL){            //Deletion of a linked list starts from the end by keeping the track of the second last node each time in a linked list
		temp = current;            //and deleting the last node of the linked list each time till the for loop in the main function is executed which keeps the total
		current = current->next;   //count of the number of nodes in the linked list.
	}
	temp->next = current->next;        //Setting the next pointer of the second last node to the next pointer of the last node in the linked list which is the NULL. 
	free(current);
	return;
}
//FUNCTION TO COUNT TOTAL NUMBER OF NODES PRESENT IN A LINKED LIST.
int countnodes(struct node *head){
	int count = 0;
	while(head != NULL){               //Everytime a node is traversed the count variable keeps on increaing to count the total number of node in the linked list.
		count++;
		head = head->next;
	}
	return count;
}
//FUNCTION TO PRINT THE DATA CONTAINED IN THE NODES OF A LINKED LIST.
void printlist(struct node *head){
	while(head != NULL){
		cout<<head->data<<" ";
		head = head->next;
	}
}
//UTILITY FUNCTION TO CHECK THE ABOVE FUNCTIONS.
int main(){
	struct node *head = NULL;

	push(&head, 12);
    push(&head, 56);
    push(&head, 2);
    push(&head, 11);
    push(&head, 10);
    push(&head, 9);
    int temp = countnodes(head);
    cout<<"List before deletion"<<endl;
    printlist(head);
    cout<<endl;
     cout<<"List after deletion::"<<endl;
    for(int i = 0; i < temp; i++)
    	deletelist(head);
    printlist(head);
    return 0;
}
