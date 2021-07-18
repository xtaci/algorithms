#include <iostream>
#include <vector>
#include <string>

using namespace std;
void swap(int* a, int* b){
    int store = *a;
    *a = *b;
    *b = store;
}

int part(int array[], int high, int low){
    int pin = array[high];
    int index = (low - 1);

    for(int i = low; i <= high; i++){
        if(array[i] <= pin){
            index++;
            swap(&array[index], &array[high]);
        }
    }
    swap(&array[index + 1], &array[high]);
    return (index + 1);
}

void quicksort(int array[], int high, int low){
    if(low < high){
        int pi = part(array,high,low);

        quicksort(array, low, pi - 1 );
        quicksort(array, pi + 1, high);
    }
}

void printArray(int array[], int size){
    int index;
    for (index =0; index < size; index++){
        cout << "" << array[index] << endl;
        cout << endl;
    }
}

int main(){
    int array[] = {25,17,3,1,22};
    int n = sizeof(array) / sizeof(array[0]);
    quicksort(array, n-1, 0);
    printArray(array, n);

}