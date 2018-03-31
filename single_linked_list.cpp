#include<stdlib.h>
#include<iostream>
#include "single_linked_list.h"
using namespace std;
int main()
{
	int choice;char ch;
	Node <int> *start=new Node<int>;//integer list or character--just change the template typename for different datatype		
	start=NULL;
		do
		{
		system("clear");
		cout<<"Enter choice: \n 0. create \n 1. insert\n 2. delete \n 3. search \n 4. display \n 5. reverse \n 6. sort \n";
		cin>>choice;
		switch(choice)
		{
			case 0:		start=start->create(start);
					break;
			case 1: 	cout<<"Enter choice: \n 1. insert at first \n 2. insert at end \n 3. insert at location \n 4. insert after element \n";
					cin>>choice;
					switch(choice)
					{
						case 1:	start=start->insertAtFirst(start);
							break;
						case 2: start=start->deleteAtEnd(start);
							break;
						case 3: start=start->deleteAtLoc(start);
							break;	
						case 4: start=start->insertAfter(start);
							break;						
					}
					break;
			case 2: 	cout<<"Enter choice: \n 1. delete at first \n 2. delete at end \n 3. delete at location \n 4. delete specific element \n";
					cin>>choice;
					switch(choice)
					{
						case 1:	start=start->deleteAtFirst(start);
							break;
						case 2: start=start->deleteAtEnd(start);
							break;
						case 3: start=start->deleteAtLoc(start);
							break;	
						case 4: start=start->deleteSpecificElement(start);
							break;						
					}
					break;
			case 3: start->search(start);
					break;
			case 4:	start->display(start);
					break;
			case 5: start=start->reverse(start);
					break;
			case 6: start=start->sort(start);
					break;
		}
			cout<<"Enter Y for continue\n";
			cin>>ch;
		}while(ch=='Y');
	return 0;
}
	
