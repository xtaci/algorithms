node* insert(node* head,int x)  //insertion at the end;
{
   node* temp=new node;
   temp->data=x;
   temp->left=0;
   temp->right=0;
   if(head==0)
   {
      head=temp;
      return head;
   }
      
   //insertion at the end; 

   node* temp1=head;
   while(temp1->right!=0)
   {
      temp1=temp1->right;
   }
   temp1->right=temp;
   temp->left=temp1;
   return head;
   
   //insertion at the beggining;
   
   temp->right=head;
   head->left=temp;
   head=temp;
}