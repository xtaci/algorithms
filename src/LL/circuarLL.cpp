#include<iostream>
using namespace std;
class node
{
	public:
		int data;
		node* link;
};
node* insert(node*,int);
void print(node*);
node* split(node*);
node* sorted_insert(node*,int);
node* head2=0;
int main()
{
	node* head=0;
    head=insert(head,1);
    head=insert(head,2);
    head=insert(head,3);
    head=insert(head,4);
    head=insert(head,7);
    head=insert(head,8);
	cout<<"circular list"<<endl;
    print(head);
    cout<<endl;
    head=sorted_insert(head,7);
    print(head);
}
void print(node* head)        //traversing circular LL;
{
	if(head==0)
		return;
	node* temp=head;
	cout<<temp->data<<" ";
	temp=temp->link;
	while(temp!=head)
	{
		cout<<temp->data<<" ";
		temp=temp->link;
	}
	return ;
}
node* insert(node* head,int x)
{
	node* temp=new node;
	temp->data=x;
	if(head==0)
	{
		head=temp;
		temp->link=head;
		return head;
	}
	node* temp1=head;
	while(temp1->link!=head)
	{
		temp1=temp1->link;
	}
	temp1->link=temp;
	temp->link=head;
	return head;
}
node* split(node* head)
{
	if(head->link->link==head)
	{
		head2=head->link;
		head->link=head;
		head2->link=head2;
		return head;
	}
	node *slow=head,*fast=head;
	while(fast->link!=head && fast->link->link!=head)
	{
		slow=slow->link;
		fast=fast->link->link;
	}
	head2=slow->link;
	slow->link=head;
	if(fast->link==head)
	{
		fast->link=head2;
	}
	else
	{
		fast->link->link=head2;
	}
	return head;
}
node* sorted_insert(node* head,int x)
{   node* temp1=head;
	node* temp=new node;
	temp->data=x;
	temp->link=0;
	if(head==0)
	{
		head=temp;
		return head;
	}
	if(x<=head->data)
	{   
		temp->link=head;
		while(temp1->link!=head)
		{
			temp1=temp1->link;
		}
		temp1->link=temp;
		head=temp;
		return head;
	}
	temp1=temp1->link;
	node *temp2=head;
	while(temp1!=head && x>temp1->data)
	{
		temp2=temp1;
		temp1=temp1->link;
	}
	temp->link=temp1;
	temp2->link=temp;
	return head;
}
