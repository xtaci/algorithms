#include<iostream>
using namespace std;
class node{
	public:
		int data;
		node* link;
};
node* insert(node* head,int x);
void print(node* head);
void eachElementOccurence(node* head,int x);
int largest(node* head);
int main()
{
	node* head =0;
	head = insert(head,1);
	head = insert(head,2);
	head = insert(head,3);
	head = insert(head,3);
	head = insert(head,9);
	head = insert(head,6);
	print(head);
	int max = largest(head);
	eachElementOccurence(head,max);
}

node* insert(node* head,int x)
{
	node* temp = new node;
	temp->data=x;
	temp->link=0;
	if(head==0)
	{
		head=temp;
		return head;
	}
	node* temp1=head;
	while(temp1->link!=0)
	{
		temp1=temp1->link;
	}
	temp1->link=temp;
	return head;
}

void print(node* head)
{
	while(head!=0)
	{
		cout<<head->data<<" ";
		head=head->link;
	}
	cout<<endl;
}
int largest(node* head)
{
	if(head==0)
		return -1;
	int large = head->data;
	while(head!=0)
	{
		if(large<head->data)
			large=head->data;
		head=head->link;	
	}
	return large;
}
void eachElementOccurence(node* head,int x)
{
	int i,hash[x+1];
	for(i=0;i<x+1;i++)
	{
		hash[i]=0;
	}
	while(head!=0)
	{
		hash[head->data]++;
		head=head->link;
	}
	for(i=0;i<=x;i++)
	{
		if(hash[i]!=0)
		{
			cout<<i<<" "<<hash[i]<<endl;
		}
	}
}

