void sum(node* head1,node* head2,node* head3,int k)   //n^3 complexity;
{
	node *temp2,*temp3;
	while(head1!=0)
		{
      	 temp2=head2;
       	 while(temp2!=0)
       		{
          	  temp3=head3;
          		while(temp3!=0)
          		{
            		if(head1->data+temp2->data+temp3->data==k)
            		{
               			cout<<head1->data<<endl;
               			cout<<temp2->data<<endl;
               			cout<<temp3->data<<end;
               			return;
            		}
            			temp3=temp3->link;
          		}
          		temp2=temp2->link;
       		}
       			head1=head1->link;
		}
	cout<<"no such triplet"<<endl;	
    return;
}