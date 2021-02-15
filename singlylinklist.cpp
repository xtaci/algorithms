#include<iostream.h>
#include<conio.h>
#include<stdlib.h>


class list
{
	struct node
	{
		int data;
		node *link;
	}*p;
public:
	void inslast(int);
	void insbeg(int);
	void insnext(int,int);
	void delelement(int);
	void delbeg();
	void dellast();
	void disp();
	int seek(int);
	list(){p=NULL;}
	~list();
};

void list::inslast(int x)
{
	node *q,*t;
	if(p==NULL)
	{
		p=new node;
		p->data=x;
		p->link=NULL;
	}
	else
	{
		q=p;
		while(q->link!=NULL)
			q=q->link;
		t=new node;
		t->data=x;
		t->link=NULL;
		q->link=t;
	}
	cout<<"
 Inserted successfully at the end..
";
	disp();
}

void list:: insbeg(int x)
{
	node *q;
	q=p;
	p=new node;
	p->data=x;
	p->link=q;
	cout<<"
 Inserted successfully at the begining..
";
	disp();
}


void list::delelement(int x)
{
	node *q,*r;
	q=p;
	if(q->data==x)
	{
		p=q->link;
		delete q;
		return;
	}
	r=q;
	while(q!=NULL)
	{
		if(q->data==x)
		{
			r->link=q->link;
			delete q;
			return;
		}
		r=q;
		q=q->link;
	}
	cout<<"
 Element u entered   "<<x<<"    is not found..
";
}

void list:: delbeg()
{
	cout<<"
 The list before deletion:
";
	disp();
	node *q;
	q=p;
	if(q==NULL)
	{
		cout<<"
 No data is present..
";
		return;
	}
	p=q->link;
	delete q;
	return;
}


void list:: dellast()
{
	cout<<"
 The list before deletion:
";
	disp();
	node *q,*t;
	q=p;
	if(q==NULL)
	{
		cout<<"
 There is no data in the list..
";
		return;
	}
	if(q->link==NULL)
	{
		p=q->link;
		delete q;
		return;
	}

	while(q->link->link!=NULL)
		q=q->link;
	q->link=NULL;
	return;
}

list::~list()
{
	node *q;
	if(p==NULL) return;
	while(p!=NULL)
	{
		q=p->link;
		delete p;
		p=q;
	}
}

void list::disp()
{
	node *q;
	q=p;
	if(q==NULL)
	{
		cout<<"
 No data is in the list..
";
		return;
	}
	cout<<"
 The items present in the list are :
";
	while(q!=NULL)
	{
		cout<<"	"<<q->data;
		q=q->link;
	}
}

void list :: insnext(int value,int position)
{
	node *temp,*temp1;
	temp=p;
	if(temp1==NULL)
	{
		temp1= new node;
		temp1->data=value;
		temp1->link=NULL;
		p=temp1;
		return;
	}
	for(int i=0;((i<position)&&(temp->link!=NULL)) ;i++)
	{
		if(i==(position-1))
		{
			temp1= new node;
			temp1->data= value;
			temp1->link=temp->link;
			temp->link=temp1;
		}
		temp=temp->link;
	}
	//cout<<"
 Inserted successfully at the position.."<<position;
	disp();
}


int list::seek(int value)
{
	node *temp;
	temp=p;
	int position=0;
	while(temp!=NULL)
	{
		if(temp->data==value)
			return position+1;
		else
		{
			temp=temp->link;
			position=position+1;
		}
	}
	cout<<"

 Element "<<value<<" not found";
	return 0;
}


void main()
{
list l;
int ch,v,p,ps;
do
{
	clrscr();
	cout<<"
 Operations on List..
";
	cout<<"
1.Insertion
2.Deletion
3.Display
4.Seek
5.Exit";
	cout<<"
 Enter ur choice:";
	cin>>ch;

	switch(ch)
	{
	case 1:
		cout<<"
1.Insertion at begining
2.Insertion at the end
";
		cout<<"3.Insertion after the mentioned position
";
		cout<<"
 Enter ur choice:";
		cin>>ps;
		cout<<"
 Enter the value to insert:";
		cin>>v;
		switch(ps)
		{
			case 1:
				l.insbeg(v);
				break;
			case 2:
				l.inslast(v);
				break;
			case 3:
				cout<<"
 Enter the position to insert the value:";
				cin>>p;
				l.insnext(v,p);
				break;

			default:
				cout<<"
 The choice is invalid
";
				return;
		}
	break;

	case 2:
		cout<<"
1.Delete the first element 
2.Delete the last element";
		cout<<"
3.Enter the element to delete from the list";
		cout<<"
 Enter ur choice:";
		cin>>ps;
		switch(ps)
		{
			case 1:
				l.delbeg();
				cout<<"
 The list after deletion:
";l.disp();
				break;
			case 2:
				l.dellast();
				cout<<"
 The list after deletion:
";l.disp();
				break;
			case 3:
				l.disp();
				cout<<"
 Enter the element to delete :	";
				cin>>v;
				l.delelement(v);
				cout<<"
 The list after deletion:
";l.disp();
				break;

			default:
				cout<<"
 The option is invalid...
";
				break;
		}
	break;

	case 3:
		l.disp();
		break;

	case 4:
		l.disp();
		cout<<"
 Enter the element to search:";
		cin>>v;
		cout<<"
 The position of the element "<< v<<"  is "<<l.seek(v);
		getch();
		break;

	case 5:
		exit(1);

	default:
		cout<<"
 The option is invalid...
";
		return;
	}
	getch();
}while(ch!=5);
getch();
return;
}
