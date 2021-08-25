#include<bits/stdc++.h>
using namespace std;

class Node{
	public:
		int data;
		Node *next; 
};

void addStart(Node** headptr, int value)
{
	Node* newnode=new Node();
	newnode->data=value;
	newnode->next=*headptr;
	*headptr=newnode;
}
void addEnd(Node** headptr, int value)
{
	Node* newnode = new Node();
	newnode->data=value;
	Node *ptr = *headptr;
	while(ptr->next!=NULL)
		ptr=ptr->next;
	ptr->next=newnode;
}
void addAfter(Node** headptr, int value, int after)
{
	Node* newnode=new Node();
	newnode->data=value;
	Node *ptr=*headptr;
	while(ptr->data!=after)
		ptr=ptr->next;
	newnode->next=ptr->next;
	ptr->next=newnode;
	return;
}
void addBefore(Node** headptr, int value, int before)
{
	Node* newnode=new Node();
	newnode->data=value;
	Node *ptr=*headptr;
	while(ptr->next->data!=before)
		ptr=ptr->next;
	newnode->next=ptr->next;
	ptr->next=newnode;
	return;
}

void print(Node** headptr)
{
	Node *ptr=*headptr;
	while(ptr!=NULL)
		{
			cout<<" "<<ptr->data;
			ptr=ptr->next;
		}
}

int main()
{
	Node* head=NULL;
	addStart(&head, 5);
	addStart(&head, 4);
	addStart(&head, 3);
	addStart(&head, 2);
	addEnd(&head, 6);
	addBefore(&head, 7, 4);
	addAfter(&head, 8, 5);
	print(&head);
}