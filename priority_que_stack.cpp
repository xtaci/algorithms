#include<bits/stdc++.h>
using namespace std;
class node{
    private:
     int data;
     node *link;
  public:
      node *pri_head=NULL;
      node *a;
      void push(int k)
      {
          node *pri_que;
          pri_que= new node();
          pri_que->data = k;
        
          if(pri_head==NULL)
          {
              pri_head=pri_que;
              pri_que->link=NULL;
              
          }
          else
          {
              
              pri_que->link=pri_head;
              pri_head=pri_que;
          }
          
      }
      void pop()
      {
          node *temp=pri_head;
          node *par=pri_head;
          if(pri_head==NULL)
          {
              cout<<"Underflow\n";
          }
          else
         {
          if(par->link==NULL)
          {
              pri_head=NULL;
          }
          else
          {
              pri_head=pri_head->link;
          /*while(temp->link!=NULL)
          {
              cout<<temp->link<<endl;
              par=temp;
              temp=temp->link;
          }
          par->link=NULL;*/
          }
         }


      }
      void show()
      {
          node *temp = pri_head;
          if(pri_head==NULL)
          {
              cout<<"Stack is empty"<<endl;
          }
          else
          {
        
          cout<<"Stack elements are :: \n";
          while(temp!=NULL)
          {   cout<<setw(6);
              cout<<"----"<<endl;
               cout<<setw(5);
              cout<<temp->data<<endl;
              
              temp=temp->link;

          }
             cout<<setw(6);
              cout<<"----"<<endl;
          }
      }
};

int main()
{
    //using priority que -- stack
     node g;
     int cases=0;
     int k,sml;
     char ch;
     while(cases!=5)
       {
           cout<<"Enter 1 for push\n"<<"Enter 2 for pop\n"<<"Enter 3 for Display\n"<<"Enter 4 for exit"<<endl;
           cin>>cases;
           switch (cases)
           {
           case 1:
           //sml=1;
           //ch=sml;
           //cout<<"Correct choice "<<ch<<endl;
            cout<<"Enter element for push :: ";
            cin>>k;
            g.push(k);
               break;

             case 2:
                   //sml=1;
                   //ch=sml;
                 // cout<<"Correct choice "<<ch<<endl;
                  g.pop();
             break; 
             case 3:
                   //  sml=1;
                   // ch=sml;
                   // cout<<"Correct choice "<<ch<<endl;
                    g.show();
                    break; 
           case 4:
                  // sml=1;
                  // ch=sml;
                 // cout<<"Correct choice "<<ch<<endl;
                  cout<<"BYE"<<endl;
                  exit(0);
              break;
        
           default:
                 // sml=2;
                  // ch=sml;
                  //cout<<"Incorrect choice "<<ch<<endl;
           cout<<"Enter valid choice"<<endl;
               break;
           }
       }
    
      

}