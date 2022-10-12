#define lln long long int
#define pb push_back
#define pop pop_back
  
  
#include<bits/stdc++.h>
using namespace std;

void reverseArray(int arr[], int start, int end)
{
    while(start<end)
    {
        int temp= arr[start];
        arr[start]= arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}
void rotateArray(int arr[], int size, int n)
{
    if(n==0)
        return;
    
    reverseArray(arr,0, n-1);
    reverseArray(arr,n, size-1);
    reverseArray(arr,0, size-1);
}

void printArray(int arr[], int size)
{
    for(int i=0; i<size; i++)
    {
        cout<<arr[i]<<" ";
    }
}
 
int main()
{
    int size; 
    int n;
    cin>>size;
    cin>>n;
    int arr[size];

    for(int i=0; i<size; i++)
    {
        cin>>arr[i];
    }
    rotateArray(arr, size, n);
    printArray(arr, size);
}