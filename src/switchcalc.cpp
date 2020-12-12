#include<iostream>
using namespace std;

int calc(int num1, int num2, int op)
{	int ans;
	switch(op)
	{
		case 1:
			ans = num1 + num2;
			break;
		case 2:
			ans = num1 - num2;
			break;
		case 3:
			ans = num1 * num2;
			break;
		case 4:
			ans = num1 / num2;
			break;
		default:
			break;
	}
	return ans;
}

	int main()
	{
		int a, b, c;
		cout<< "Type respective number to choose an operator\n";
		cout<< "+\t-\t*\t/\n";
		cout<< "1\t2\t3\t4\n";
		cin >> c;
		cout<<"Enter the numbers\n";
		cin >>a>>b;
		cout<<calc(a, b, c);
	}
