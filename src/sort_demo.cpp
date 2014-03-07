
#include <cstdlib>
#include <iostream>
#include "sort.h"

using namespace std;
using namespace alg;


/////////////////////////////
//
//	custom compare function
//	
/////////////////////////////
bool comp(int a,int b){
	if (a>=b)
		return true;

	return false;
}

/////////////////////////////
//
//	custom swap function
//
///////////////////////////////
void swap(int &a,int &b){
	int tmp;
	tmp=a;
	a=b;
	b=tmp;
}


//make rand data
void makeArray(vector<int>& array,int num){
		
	for(size_t i = 0; i < num; ++i)
	{
		array.push_back(rand()%100);
		/* code */
	}
	
}


int main (int argc, char const *argv[])
{
	vector<int> a;
	
	alg::SortClass<int> sort(a,comp,swap);
	makeArray(a,10);
	cout << "############### quick sort ###############" << endl;
	cout << "before sort::: " ;
	sort.displaySort();
	sort.quickSort();
	cout << "after sort ::: ";
	sort.displaySort();
	cout << endl;
	
	
	a.clear();
	makeArray(a,11);
	cout << "############### insertion sort ###############" << endl;
	cout << "before sort::: " ;
	sort.displaySort();
	sort.insertSort();
	cout << "after sort ::: ";
	sort.displaySort();
	cout << endl;
	
	
	a.clear();
	makeArray(a,10);
	cout << "############### bubble sort ###############" << endl;
	cout << "before sort::: " ;
	sort.displaySort();
	sort.bubbleSort();
	cout << "after sort ::: ";
	sort.displaySort();
	cout << endl;
	
	
	a.clear();
	makeArray(a,10);
	cout << "############### selection sort ###############" << endl;
	cout << "before sort::: " ;
	sort.displaySort();
	sort.selectionSort();
	cout << "after sort ::: ";
	sort.displaySort();
	cout << endl;
	
	
	a.clear();
	makeArray(a,10);
	cout << "############### heap sort ###############" << endl;
	cout << "before sort::: " ;
	sort.displaySort();
	sort.heapSort();
	cout << "after sort ::: ";
	sort.displaySort();
	cout << endl;
	
	a.clear();
	makeArray(a,10);
	cout << "############### merge sort ###############" << endl;
	cout << "before sort::: " ;
	sort.displaySort();
	sort.mergeSort();
	cout << "after sort ::: ";
	sort.displaySort();
	
	
	
	return 0;
}
