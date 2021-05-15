/*
Author : Aswin Sampath 
Topic : Counting Sort

                            Counting Sort
    When to use?
        Vizualise the array/vector elements 
        Amount of space needed by the algorithm = Range of the vector
        Range of vector = Max(vector)- Min(vector)
        If Range is of the order 10^5 then we can use counting sort subjet to the compiler 

    How to Implement 
        Sort the numbers according to their frequency/ number of occurences
        Place the element in their respective position according to the ranking 

    Time Complexity : O(n)
    Space COmplexity : O(Max(arr)-Min(arr));
*/


#include<iostream>
#include<vector>
using namespace std;

void printVector(vector<int>v){
    cout<<"\n Vector elements \n ";
    for(int element:v){
        cout<<element<<" ";
    }
    cout<<"\n";
}

int findMin(vector<int>arr){
    int minele = arr[0];
    for(int ele:arr){
        if(ele<=minele)minele=ele;
    }
    return minele;
}

int findMax(vector<int>arr){
    int maxele = arr[0];
    for(int ele:arr){
        if(ele>=maxele)maxele=ele;
    }
    return maxele;
}


int findRange(vector<int>arr){
    int maxele = findMax(arr);
    int minele = findMin(arr);
    return maxele - minele;
}

vector<int>freq;
vector<int>output;

void countingSort(vector<int> &arr,int range){

    // cout<<"Size of arr = "<<arr.size()<<"\n";
    output.resize(arr.size());
    freq.resize(range+1);
    
    // Find the frequency for each element in the array
    for(int ele : arr){
        freq[ele]++;
    }
    //printVector(freq);

    // Find the ranking for each element by using prefix sum 
    for(int i=1;i<freq.size();i++){
        freq[i]+=freq[i-1];
    }
    //printVector(freq);
    /* Ranking  table
    number  rank
    0   -   1
    1   -   3
    2   -   7
    3   -   10
    4   -   14
    5   -   17
    6   -   21
    7   -   25
    8   -   28
    9   -   30

    */

    // Arrange the Elements according their rank
    for(int i=0;i<arr.size();i++){
        int num = arr[i]; //The number in the array
        int rank = freq[num]; // The rank of the number
        output[rank-1]= num; // Since indexing starts from and rank from 1 we need to adjust the difference
        freq[num]--; // Decrease the freq count of the number once it has been written to output
    }
    //printVector(output);

    // Rewrite the output to the original array
    for(int i=0;i<arr.size();i++){
        arr[i]=output[i];
    }
    output.resize(0); // Free the output array space
    cout<<"\n";
}

int main(){
    
    // TODO : Sort the below array
    vector<int>arr = {2,3,7,4,6,8,9,2,5,4,8,3,1,6,7,2,5,7,6,1,4,2,3,9,8,7,4,5,6,0};
    
    /* Frequency Table
    ele     freq
    0   -   1   
    1   -   2
    2   -   4
    3   -   3
    4   -   4
    5   -   3
    6   -   4
    7   -   4
    8   -   3
    9   -   2
    */

    // Vector Range = max(arr)-min(arr) = 9 - 0 = 9 Hence we require of a 9 space in frequency array
    int range = findRange(arr);
    cout<<"Before Sorting \n";
    printVector(arr);
    countingSort(arr,range); // Sorting algorithm
    cout<<"After Sorting \n";
    printVector(arr);
}

