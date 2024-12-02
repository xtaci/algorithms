// inserting node at the end in linked list;
//program also includes a function where an element is added to list without affecting its sorted nature;
// program to delete duplicate elements;  
//largest element in ll;
//rotate ll;
//duplicate ll;
//split the given list into two lists;
#include<iostream>
using namespace std;
class node{
	public:
	int data;
	node* link;
};
node* head1=0;  //global declaration;
node* head2=0;  //global declaration;
node* insert(node*,int);
void print(node*);
node* sortedinsert(node* ,int);
node* delete_dup(node* head);
int large_element(node* head);
node* alt_split(node* head);
node* rotate(node*);
node* duplicate(node*);
node* sort_duplicate(node*);
node* swap_node_data(node* head);
node* rec_swap_node_data(node* head);
void swap(int *x,int *y);
node* split(node*);
int main()
{   node *head=0;
    int n,i,x;
	cout<<"enter no. of elements to be added"<<endl;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>x;
		head=insert(head,x);
	}
	print(head);
	cout<<endl;
	head=split(head);
	print(head);
	print(head1);
	print(head2);
}
node* insert(node* head,int x)
{
	node *temp=new node();
	temp->data=x;
	temp->link=0;
	if(head==0)
	head=temp;
	else
	{
		node *temp1=head;
		while(temp1->link!=0)
		{
			temp1=temp1->link;
		}
		temp1->link=temp;
	}
	return head;
}
void print(node* head)
{
	cout<<"list:-"<<endl;
	node *temp=head;
	while(temp!=0)
	{
		cout<<temp->data<<" ";
		temp=temp->link;
	}
}
node* sortedinsert(node* head,int x)
{
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
	   head=temp;
	   return head;	
	}
    node* temp1=head;
    node* temp2;
	while(temp1!=0&&temp1->data<x)
    {
    	temp2=temp1;
    	temp1=temp1->link;
	}
	temp->link=temp1;
	temp2->link=temp;
	return head;
}
node* delete_dup(node* head)
{
	node* temp1=head;
	node* temp2,temp3;
	int x;
	while(temp1!=0)
	{
		x=temp1->data;
		node* temp3=temp1;
		temp2=temp1->link;
		while(temp2!=0)
		{
			if(temp2->data==x)
			{
			  	temp3->link=temp2->link;
			  	delete temp2;
			  	temp2=temp3->link;
			}
			else
			{
			   	temp2=temp2->link;
			   	temp3=temp3->link;
			}
		}
		temp1=temp1->link;
	}
	return head;
}
int large_element(node* head)
{   if(head->link==0)
   {
      return head->data;	
   }
	node* temp1=head;
	node* temp2=head->link;
	while(temp2!=0)
	{
		if(temp1->data<temp2->data)
		temp1=temp2;
		temp2=temp2->link;
	}
	return temp1->data;
}
node* alt_split(node* head)
{   if(head->link==0)
	{
		return head;
	}
	int p;
	node* head1=head;
	node* temp1=head;
	head=head->link;
	node* temp2=head;
	head2=head;
	head=head->link;
	p=3;
	while(head!=0)
	{
       if(p%2==0)
       { 
       	 temp2->link=head;
       	 temp2=head;
       }
       else
       {
       	temp1->link=head;
        temp1=head;
       }
       head=head->link;
       p++;
	}
	temp1->link=0;
	temp2->link=0;
	return head1;
}
node* rotate(node* head)
{
	if(head->link==0)
	{
	   return head;
	}
    node* temp=head;
    while(temp->link->link!=0)
    {
      temp=temp->link;
    } 
    temp->link->link=head;
    head=temp->link;
    temp->link=0;
    return head;
}
node* duplicate(node* head)
{
	if(head==0)
	{
	   return head;
	}
	node *head1=head,*temp1,*temp2;
	while(head1!=0)
	{
       temp2=head1;
       temp1=head1->link;
       while(temp1!=0)
       {
          if(temp1->data==head1->data)
          {
             temp2->link=temp1->link;
             delete temp1;
             temp1=temp2->link;
          }
          else
          {
             temp1=temp1->link;
             temp2=temp2->link;
          }
       }
       head1=head1->link;
	}
	return head;
}
node* sort_duplicate(node* head)  //remove duplicae elements of sorted list;
{   if(head==0)
    return head;
	node* temp1=head;
	node* temp2=head->link;
	while(temp2!=0)
	{
	  if(temp2->data==temp1->data)
      {
        temp1->link=temp2->link;
        delete temp2;
        temp2=temp1->link;
      }
      else
      {
         temp1=temp1->link;
         temp2=temp2->link;
      }
	}
	return head;
}
node* swap_node_data(node* head)  //iterative way
{   if(head==0)
    return head;
	node* temp=head;
    while(temp!=0 && temp->link!=0)
    {
        swap(&temp->data,&temp->link->data);
        temp=temp->link->link;
    }
    return head;
}
void swap(int *x,int *y)
{
	int z;
	z=*x;
	*x=*y;
	*y=z;
}
node* rec_swap_node_data(node* head)
{
	if(head==0||head->link==0)
	{
		return head;
	}
	swap(&head->data,&head->link->data);
	rec_swap_node_data(head->link->link);
	return head;
}
node* split(node* head)
{
	node* temp1=head1;
	node* temp2=head2;
	node* temp;
	int n=1;
	while(head!=0)
	{
	    if(n%2!=0)
        {
           temp=head;
           head=temp->link;
           temp->link=0;
             if(head1==0)
             {
                 head1=temp;
                 temp1=temp;
             }
             else
             {
                 temp1->link=temp;
                 temp1=temp;
             }
        }
        else
        {
            temp=head;
            head=temp->link;
            temp->link=0;
             if(head2==0)
             {
                 head2=temp;
                 temp2=temp;
             }
             else
             {
                 temp2->link=temp;
                 temp2=temp;
             }   
        }
        n++;
	}
	return head;
}
