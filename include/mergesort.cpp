#include<iostream>
using namespace std;
void merge(int A[], int low, int mid, int high)
{
	int k=low,i=low,j=mid+1,c[100];
	while((i<=mid)&&(j<=high))
	{
		if(A[i]<=A[j])
		{
			c[k] = A[i];
			i++;
		}
		else if(A[i]>=A[j])
		{
			c[k] = A[j];
			j++;
		}
		k++;
	}
	if(k>mid)
	while(i<=mid)
	{
		c[k] = A[i];
		i++;
		k++;
	}
	while(j<=high)
	{
		c[k] = A[j];
		j++;
		k++;
	}
	for(int i=low; i <=high; i++)
		A[i] = c[i];
}
void mergesort(int A[], int low, int high)
{
	if(low < high)
	{
		int mid = (low+high)/2;
		mergesort(A,low,mid);
		mergesort(A,mid+1,high);
		merge(A,low,mid,high);
	}
}
int main()
{
	cout<<"Enter size of array"<<endl;
	int n;
	cin>>n;
	cout<<"Enter array to be sorted"<<endl;
	int array[100];
	for(int i = 0; i < n; i++)
		cin>>array[i];
	mergesort(array,0,n-1);
	cout<<"Array after sorting"<<endl;
	for(int i = 0; i < n; i++)
		cout<<array[i]<<" ";
	return 0;
}