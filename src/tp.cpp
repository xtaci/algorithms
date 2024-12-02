#include<bits/stdc++.h>
using namespace std;

class Node{
public:
    int data;
    Node *next; 
};

void addNode(Node** headptr, int value)
{
    Node* newnode = new Node();
    newnode->data=value;
    newnode->next= *headptr ;
    *headptr=newnode;

    return;
}
void addEnd(Node** headptr, int value)
{
    Node* newnode = new Node();
    newnode->data=value;
    Node *ptr=*headptr;
    newnode->next = NULL;
    while(ptr->next!=NULL)
    {
        ptr=ptr->next;
    }
    ptr->next=newnode;
    return;
}

void addAfter(Node* after, int value)
{
    Node* newnode = new Node();
    newnode->data=value;
    newnode->next=after->next;
    after->next=newnode;
}


void addBefore( Node** headptr,int before, int value )
{
    Node* newnode=new Node();
    newnode->data=value;
    Node *ptr = *headptr;
    while(ptr->next->data!=before)
    {
        ptr = ptr->next;
    }
    newnode->next=ptr->next;
    ptr->next=newnode;
    return;

}

void printll(Node** headptr)
{
    Node *ptr = *headptr;
    while(ptr != NULL)
    {
        cout<<" "<<ptr->data;
        ptr=ptr->next;
    }
}

int main()  
{  
  Node* head = NULL;  
  addNode(&head, 4);  
  addNode(&head, 7);  
  addNode(&head, 1);  
  addNode(&head, 4);  
  addEnd(&head, 9);
  addEnd(&head, 2); 
  addAfter(head->next->next, 8); 
  addBefore(&head, 8, 5); 

    
  // cout<<"Created Linked list is: ";  
  // printll(&head);
  // cout<<endl<<head<<endl;
  // cout<<endl<<&head;
  Node* a = new Node();  Node* b = new Node();  Node* c = new Node(); 
  a->next=b;b->next=c;c->next=NULL;
  a->data=10;b->data=20;c->data=30;
  printll(&a);

  cout<<endl<<&a;  cout<<endl<<&b;  cout<<endl<<&c;
  cout<<endl;

  cout<<endl<<&a->next;  cout<<endl<<&b->next;  cout<<endl<<&c->next;
  cout<<endl;

  cout<<endl<<&a->data;  cout<<endl<<&b->data;  cout<<endl<<&c->data;
  cout<<endl;










    
  return 0;  
}  

-2147483412
