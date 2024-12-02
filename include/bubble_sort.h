/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * BUBBLE SORT
 *
 *   Bubble sort, sometimes incorrectly referred to as sinking sort, is a simple
 * sorting algorithm that works by repeatedly stepping through the list to be 
 * sorted, comparing each pair of adjacent items and swapping them if they are 
 * in the wrong order. The pass through the list is repeated until no swaps are
 * needed, which indicates that the list is sorted. The algorithm gets its name
 * from the way smaller elements "bubble" to the top of the list. Because it 
 * only uses comparisons to operate on elements, it is a comparison sort. 
 * Although the algorithm is simple, most of the other sorting algorithms are 
 * more efficient for large lists.
 *
 * http://en.wikipedia.org/wiki/Bubble_sort
 ******************************************************************************/

#ifndef _BUBBLE_SORT_H_
#define _BUBBLE_SORT_H_

#include <bits/stdc++>
using namespace std;

template <class X> void bubble(X *items,int count)
{
  X t;

  for(int a=1; a<count; a++)
    for(int b=count-1; b>=a; b--)
      if(items[b-1] > items[b]) {
        t = items[b-1];
        items[b-1] = items[b];
        items[b] = t;
      }
}

int main()
{
  int iarray[7] = {7, 5, 4, 3, 9, 8, 6};
  double darray[5] = {4.3, 2.5, -0.9, 10.2, 3.0};

  cout << "Here is unsorted integer array: ";
  for(int i=0;  i<7; i++)
    cout << iarray[i] << ' ';
  cout << endl;

  bubble(iarray, 7);

  cout << "Here is sorted integer array: ";
  for(int i=0;  i<7; i++)
    cout << iarray[i] << ' ';
  cout << endl;

  cout << "Here is unsorted double array: ";
  for(int i=0;  i<5; i++)
    cout << darray[i] << ' ';
  cout << endl;

  bubble(darray, 5);

  cout << "Here is sorted double array: ";
  for(int i=0;  i<5; i++)
    cout << darray[i] << ' ';
  cout << endl;

  return 0;
}
