//deletion of node at end;
#include<iostream>
using namespace std;
class node 
{
  public:
  int data;
  node* link;	
};
void insert(int x);
void remove();
void print();
node *head=0;
int main()
{
	insert(1);
	insert(2);
	insert(3);
    insert(4);
    insert(5);
    cout<<"initial list"<<endl;
    print();
	remove();
	cout<<"list after first removal"<<endl;
	print();
	remove();
	cout<<"list after second removal"<<endl;
	print();
}
void insert(int x)
{
	node *temp=new node;
	temp->data=x;
	temp->link=0;
	if(head==0)
	{
		head=temp;
		return;	
	}
	node* temp1=head;
	while(temp1->link!=0)
	{
		temp1=temp1->link;
	}
	temp1->link=temp;
}
void remove()
{
	if(head==0)
	return ;
	if(head->link==0)
	{
		head=0;
		return;
	}
	node* temp1=head;
	node* temp2=head;
	while(temp1->link!=0)
	{
		temp2=temp1;
		temp1=temp1->link;
	}
	delete temp1;
	temp2->link=0;
}
void print()
{
	node* temp=head;
	while(temp!=0)
	{
		cout<<temp->data<<endl;
		temp=temp->link;
	}
}
