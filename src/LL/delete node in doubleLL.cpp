//delete node at any position;
node* remove(node* head,node* temp)
{   node *temp1,*temp2;
	if(temp->left==0&&temp->right==0)
	{
	    delete temp;
	    head=0;
	}
	else if(temp->right==0)
	{
	   temp1=temp->left;
	   temp1->right=0;
	   delete temp;
	}
	else if(temp->left==0)
	{
	   temp2=temp->right;
	   temp2->left=0;
	   delete temp;
	}
	else
	{
	   temp1=temp->left;
       temp2=temp->right;
       temp1->right=temp2;
       temp2->left=temp1;
       delete temp;
	}
	return head;
}