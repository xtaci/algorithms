/* **********************************************
	SINGLE LINKED LIST
	menu-driven demo program in single_linked_list.cpp

*/


#include<stdlib.h>
#include<iostream>
using namespace std;
template<typename X>class Node
{
	X data;
	Node *address;
	public:	Node(){};
		Node(X a);
		Node * create(Node *);
		Node * insertAtFirst(Node *);
		Node * insertAtLast(Node *);
		Node * insertAtLoc(Node *);
		Node * insertAfter(Node *);
		Node * deleteAtEnd(Node *);
		Node * deleteAtFirst(Node *);
		Node * deleteAtLoc(Node *);
		Node * deleteSpecificElement(Node *);	
		void search(Node *);
		void display(Node *);
		Node * sort(Node *);
		Node * reverse(Node *);
};
template<typename X> Node<X>::Node(X a)
{
	data=a;
	address=NULL;
}
template<typename X>Node<X> * Node<X>::create(Node * start)
{
	X a;
	cout<<"Enter the data\n";
	cin>>a;
	Node *ptr=new Node(a);
	Node *temp;
	temp=start;
	if(start==NULL)
		start=ptr;
	else
	{
		while(temp->address!=NULL)
		{
			temp=temp->address;
		}
		temp->address=ptr;
	}
	return start;
} 
template<typename X> Node<X> * Node<X>::insertAtLast(Node * start)
{
	X a;
	cout<<"Enter the data\n";
	cin>>a;
	Node *ptr=new Node(a);
	Node *temp;
	temp=start;
	if(start==NULL)
		start=ptr;
	else
	{
		while(temp->address!=NULL)
		{
			temp=temp->address;
		}
		temp->address=ptr;
	}
	return start;
} 
template<typename X> Node<X> * Node<X>::insertAtFirst(Node * start)
{
	X a;
	cout<<"Enter the data\n";
	cin>>a;
	Node *ptr=new Node(a);
	if(start==NULL)
		start=ptr;
	else
	{
		ptr->address=start;
		start=ptr;
	}
	return start;
}

template<typename X> void Node<X>::display(Node * start)
{	
	Node *temp; Node *temp1;
	temp=start;
	if(temp==NULL)
		cout<<"List is Empty\n";
	else
	{
		do
		{
			cout<<temp->data<<"    ";
			temp=temp->address;				
		}while(temp!=NULL);
		cout<<endl;
	}
}
template<typename X>Node<X> * Node<X>::insertAtLoc(Node * start)
{
	X a; int count=1,loc;
	Node *temp;
	temp=start;
	cout<<"Enter the location where you want to insert\n";
	cin>>loc;
	
	if(loc==1)
		start=start->insertAtFirst(start);
	else
	{
	while(count!=loc-1 && temp!=NULL)
	{
		temp=temp->address;
		count++;
	}
	if(temp==NULL)
		cout<<"Invalid location\n";
	else	
	{
		cout<<"Enter the data\n";
		cin>>a;
		Node *ptr=new Node(a);
		ptr->address=temp->address;
		temp->address=ptr;
	}
	}
	return start;
}
template<typename X>Node<X> * Node<X>::insertAfter(Node * start)
{
	X a; int count=1,item;
	Node *temp,*prev;
	temp=start;
	if(start==NULL)
		cout<<"List is empty\n";
	else
	{
	cout<<"Enter the element after which you want to insert\n";
	cin>>item;
	
	while(temp!=NULL && temp->data!=item)
	{
		temp=temp->address;
		count++;
	}
	if(temp==NULL)
		cout<<"Invalid element\n";
	else	
	{
		cout<<"Enter the data\n";
		cin>>a;
		Node *ptr=new Node(a);
		ptr->address=temp->address;
		temp->address=ptr;
	}
	}
	return start;
}
template<typename X>Node<X> * Node<X>::deleteAtEnd(Node * start)
{
	Node * temp,*prev;
	temp=start;
	if(start==NULL)
		cout<<"list is enpty";
	else
	{
	while(temp->address!=NULL)
	{	
		prev=temp;
		temp=temp->address;
	}
	prev->address=temp->address;
	delete temp;
	}
	return start;
}
template<typename X>Node<X> * Node<X>::deleteAtFirst(Node * start)
{
	if(start==NULL)
		cout<<"list is empty\n";
	else
	{
		Node *temp=start;
		start=start->address;
		delete temp;
	}
	return start;
}
template<typename X>Node<X> * Node<X>::deleteAtLoc(Node * start)
{
	Node * temp,*intermediate;int loc,count=1;
	temp=start;
	if(start==NULL)
		cout<<"List is Empty\n";
	else if(loc==1)
	{
		cout<<"enter location where to delete\n";
		cin>>loc;
		start=start->deleteAtFirst(start);
	}
	else
	{
		cout<<"enter location where to delete\n";
		cin>>loc;
		while(count!=loc-1 && temp->address!=NULL)
		{
			temp=temp->address;
			count++;
		}
		if(temp->address==NULL)
			cout<<"Invalid Location\n";
		else
		{
			intermediate=temp->address;
			temp->address=intermediate->address;
			delete intermediate;
		}
	}
	return start;	
}
template<typename X>Node<X> * Node<X>::deleteSpecificElement(Node * start)
{
	Node * temp,* prev;
	temp=start;
	X item;
	if(start==NULL)
		cout<<"List is Empty\n";
	else if(start->data==item)
	{
		cout<<"Enter element to be deleted\n";
		cin>>item;
		start=start->address;
		delete temp;
	}
	else
	{
		cout<<"Enter element to be deleted\n";
		cin>>item;
		while(temp!=NULL && temp->data!=item)
		{
			prev=temp;
			temp=temp->address;
		}
		if(temp==NULL)
			cout<<"element not present\n";
		else
		{
			prev->address=temp->address;
		}
		delete temp;
	}
	return start;
}
template<typename X>void Node<X>::search(Node * start)
{
	Node * temp;
	temp=start;
	X item;
	cout<<"Enter element to be searched\n";
	cin>>item;
	if(start==NULL)
		cout<<"Empty list\n";
	else
	{
		while(temp!=NULL)
		{
			if(temp->data==item)
				 break;
			temp=temp->address;
		}
		if(temp!=NULL)
			cout<<"Element found\n";
		else
			cout<<"Element not found\n";
	}
}
template<typename X>Node<X> * Node<X>::sort(Node * start)
{
	Node *temp1,*temp2;int t;
	temp1=start;
	if(start==NULL)
		cout<<"List is empty. Nothing to sort\n";
	else
	{
	while(temp1!=NULL)
	{
		temp2=temp1->address;
		while(temp2!=NULL)
		{
			if(temp2->data<temp1->data)
			{
				t=temp1->data;
				temp1->data=temp2->data;
				temp2->data=t;
			}
			temp2=temp2->address;
		}
		temp1=temp1->address;
	}
	}
	return start;
} 
template<typename X>Node<X> * Node<X>::reverse(Node * start)
{
	Node *p1,*p2,*temp;
	p1=start;
	if(start==NULL)
		cout<<"List is Empty. Nothing to reverse\n";
	else if(start->address==NULL)
		return start;
	else
	{
	p2=p1->address;
	while(p2!=NULL)
	{
		
		temp=p2->address;
		p2->address=p1;
		p1=p2;
		p2=temp;
	}
	start->address=NULL;
	start=p1;
	}
	return start;
}
