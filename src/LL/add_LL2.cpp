#include<iostream>
using namespace std;
class node{
	public:
	int data;
	node* link;	
};
void print(node*);
node* add(node* ,node* ,node*);
node* insert(node* ,int);
int main()
{   int i;
	node *head=0;
	node* head2=new node;
	head2->data=0;
	head2->link=0;
	node* head3=new node;
	head3->data=0;
	head3->link=0;
	for(i=1;i<10;i++)
	{
		head2=insert(head2,i);
		head3=insert(head3,i);
	}
	cout<<"head2 list"<<endl;
	print(head2);
	cout<<endl<<"head3 list"<<endl;
	print(head3);
	head=add(head,head2,head3);
	cout<<endl<<"head list"<<endl;
	print(head);
}
node* insert(node* head,int x)
{
	head->data++;
	node* temp=new node;
	temp->data=x;
	temp->link=0;
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
	node* temp=head->link;
	while(temp!=0)
	{
		cout<<temp->data<<" ";
		temp=temp->link;
	}
}
node* add(node* head,node* head2,node* head3)
{  int x;
   node* temp1;
   if(head2->data<=head3->data)
{   head=head3;
	head2=head2->link;
	head3=head3->link;
	int y=0;
	while(head2!=0)
	{
		x=(head2->data+head3->data+y)%10;
		y=(head2->data+head3->data+y)/10;
		head3->data=x;
		head2=head2->link;
		if(head3->link==0)
		temp1=head3;
		head3=head3->link;
	}
	while(head3!=0)
	{
  		x=(head3->data+y)%10;
  		y=(head3->data+y)/10;
  		head3->data=x;
  		if(head3->link==0)
		temp1=head3;
		head3=head3->link;	
	}
	if(y==1)
    {
	node* temp=new node;
	temp->data=1;
	temp->link=0;
	temp1->link=temp;
	head->data++;
    }
}
else
{
	head=head2;
	head2=head2->link;
	head3=head3->link;
	int y=0;	
	while(head3!=0)
	{
		x=(head2->data+head3->data+y)%10;
		y=(head2->data+head3->data+y)/10;
		head2->data=x;
		if(head2->link==0)
		temp1=head2;
		head2=head2->link;
		head3=head3->link;
	}
	while(head2!=0)
	{
  		x=(head2->data+y)%10;
  		y=(head2->data+y)/10;
  		head2->data=x;
  		if(head2->link==0)
		temp1=head2;
		head2=head2->link;	
	}
	if(y==1)
	{
	node* temp=new node;
	temp->data=1;
	temp->link=0;
	temp1->link=temp;
	head->data++;
    }
}	
return head;
}
