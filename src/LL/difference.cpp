#include<iostream>
#include<list>
#include<iterator>
using namespace std;
int main()
{
	list<int>l1;
	list<int>l2;
	list<int>::iterator i1;
	list<int>::iterator i2;
	l1.push_back(3);
	l1.push_back(0);
	l1.push_back(1);
	l1.push_back(0);
	l2.push_back(2);
	l2.push_back(9);
	l2.push_back(2);
	//l2.push_back(0);
	l1.reverse();
	l2.reverse();
	i1=l1.begin();
	i2=l2.begin();
	int data,x=0;
	list<int>l3;
	while(i1!=l1.end() && i2!=l2.end())
	{
		if(x==1)
		{
			if(*i1!=0)
			{
			
				*i1=*i1-1;
				x=0;
			}
			else
			{
				*i1=9;
			}
		}
		
		if(*i1>=*i2)
		{
			data=*i1-*i2;
			l3.push_back(data);
			i1++;
			i2++;
		}
		else
		{
			data = 10+ *i1-*i2;
			l3.push_back(data);
			i1++;
			i2++;
			x=1;
		}
	}

	while(i1!=l1.end())
	{
		if(x==1)
		{
			if( (*i1) !=0)
			{
				(*i1)--;
				x=0;
			}
			else
			{
				*i1=9;
			}
		}
			data=*i1;
			l3.push_back(data);
			i1++;
	}
	l3.reverse();
	list<int>::iterator i=l3.begin();
	for(i;i!=l3.end();i++)
	{
		cout<<*i<<" ";
	}
}
