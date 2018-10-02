//clone a linked list
#include<iostream>
#include<vector>
using namespace std;
class node{
	public:
	int data;
	node* next;
	node* prev;
}; 
node* check(node* head);
node* newnode(int x);
void print(node* head1);
node* newnode(int x){
	node* temp=new node;
	temp->data=x;
	temp->next=0;
	temp->prev=0;
}
int main()
{
		node* head=newnode(1);
		head->next=newnode(2);
		head->next->next=newnode(3);
		head->next->next->next=newnode(4);
		head->prev=head->next->next;
		head->next->prev=head->next->next->next;
		head->next->next->prev=head->next;
		head->next->next->next->prev=head;
		node* head1=check(head);
		print(head1);
}
void print(node* head1)
{
	while(head1!=0)
	{
		cout<<head1->data<<" ";
		head1=head1->next; 
	}
}
node* check(node* head)
{
	if(head==0)
	{
		return 0;
	}
	node* temp=head;
	node *head1=0,*temp1;
	vector<node*>v;
	while(temp!=0)
	{
		if(head1==0)
		{
			head1=newnode(temp->data);
			temp1=head1;
			temp=temp->next;
		}
		else
		{
			temp1->next=newnode(temp->data);
			temp1=temp1->next;
			temp=temp->next;
		}
		v.push_back(temp);
	}
	temp=head;
	temp1=head1;
	int i=0;
	while(temp!=0)
	{
		temp->next=temp1;
		temp1->prev=temp;
		temp1=temp1->next;
		temp=v[i];
		i++;
	}
	temp=head;
	temp1=head1;
	while(temp1!=0)
	{
		temp1->prev=temp1->prev->prev->next;
		temp1=temp1->next;
	}i=0;
	while(temp!=0)
	{
		temp->next=v[i];
		temp=temp->next;
		i++;
	}
	return head1;
}
