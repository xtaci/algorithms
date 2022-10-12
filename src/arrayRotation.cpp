
#include<bits/stdc++.h>
using namespace std;

void printArray(int arr[], int n)
{
    for(int i=0; i<n; i++)
        cout<<arr[i]<<" ";
}

void rotateElement(int arr[], int n)
{
    int temp = arr[0];
    for(int i=0; i<n-1; i++)
    {
        arr[i]=arr[i+1];
    }

    arr[n-1]=temp;
}

void rotateArray(int arr[], int n, int diff)
{
    for(int i=0; i<diff; i++)
        rotateElement(arr, n);
}

int main()
{
    int n;
    cin>>n;

    int arr[n];
    for(int i=0; i<n; i++)
    {
        cin>>arr[i];
    }

    int diff;
    cin>>diff;

    rotateArray(arr, n, diff);
    printArray(arr, n);
}