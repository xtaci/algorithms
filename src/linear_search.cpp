#include <iostream>
#include <vector>
using namespace std;

int linearSearch(vector<int> &arr, int value)
{
	for (int i = 0; i < arr.size(); ++i)
		if (arr[i] == value)
			return i;
	return -1;
}

int main()
{
	vector<int> arr {3, -12, 29432, 0, 42, 9, -23, 3};
	int value;
	cin >> value;
	int index = linearSearch(arr, value);
	if (index >= 0)
		cout << value << " is present in the array at index "
	      	 << index << ".\n";
	else
		cout << value << " isn't present in the array.\n";

	return 0;
}
