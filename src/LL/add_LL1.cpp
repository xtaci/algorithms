//add two linked list and store result in third list;
//creating new list consisting of common nodes of two input lists;
#include<iostream>
using namespace std;
class node{
	public:
	int data;
	node* link;
};
void print(node* head);
node* insert(node* ,int);
node* sum(node* ,node*,node*);
node* common_nodes(node* head1,node* head2,node* head);
int main()
{
	node *head1=0,*head2=0,*head3=0;
	head1=insert(head1,1);
	head1=insert(head1,2);
	head1=insert(head1,3);
	head1=insert(head1,4);
	head1=insert(head1,6);
	print(head1);
	cout<<endl;
	head2=insert(head2,3);
	head2=insert(head2,5);
	print(head2);
	cout<<endl;
	head3=common_nodes(head1,head2,head3);
	print(head3);
}
node* sum(node* head1,node* head2,node* head3)
{
	if(head1==0)
	{
		head3=head2;
		return head3;
	}
	if(head2==0)
	{
		head3=head1;
		return head3;
	}
	int x=0,y=0;
	node* temp1=new node;
	head3=temp1;
	node* temp=temp1;
	while(head1!=0&&head2!=0)
	{   
		x=head1->data+head2->data;
		temp->data=(x+y)%10;
		y=(x+y)/10;
		head2=head2->link;
		head1=head1->link;
		temp1=new node;
		temp->link=temp1;
		temp=temp1;
	}
	while(head1!=0)
	{
		temp->data=(head1->data+y)%10;
		y=(head1->data+y)/10;
		head1=head1->link;
		temp1=new node;
		temp->link=temp1;
		temp=temp1;
	}
	while(head2!=0)
	{
		temp->data=(head2->data+y)%10;
		y=(head2->data+y)/10;
		head2=head2->link;
		temp1=new node;
		temp->link=temp1;
		temp=temp1;
	}
    if(y==1)
    {
    	temp->data=y;
    	return head3;
	}
    temp->data=0;
    temp->link=0;
	return head3; 
}
node* insert(node* head,int x)
{
	node* temp=new node;
	temp->data=x;
	temp->link=0;
	if(head==0)
	{
		head=temp;
		return head;
	}
	node *temp1=head;
	while(temp1->link!=0)
	{
		temp1=temp1->link;
	}
	temp1->link=temp;
	return head;
}
void print(node *head)
{
	if(head==0)
	{
		return;
	}
	node *temp=head;
	while(temp!=0)
	{
		cout<<temp->data<<" ";
		temp=temp->link;
	}
}
node* common_nodes(node* head1,node* head2,node* head)
{   
	node *temp2;
	while(head1!=0)
	{
	  temp2=head2;
	  while(temp2!=0&&head1->data>=temp2->data)
	  {
	    if(head1->data>temp2->data)
	    {
           temp2=temp2->link;
	    }
	    else
	    {
	       head=insert(head,head1->data);
	       break;
	    }
	  }
	  head1=head1->link;
	}
	return head;
}
