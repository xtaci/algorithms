#include<iostream>
using namespace std;

int main()
{
	string halwa = "rishabhkumar";
	cout << halwa << endl;

	cout << halwa.length() <<"\n";
	cout << halwa.substr(7, halwa.length()) << "\t" << halwa.substr(0,4);
	getline(cin, halwa);
	cout << halwa;
	cin >> halwa;
	cout << halwa;
}