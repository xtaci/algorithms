


#ifndef _bubble_sort_h_
#define _bubble_sort_h_


#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>


using namespace std;

namespace aglo{
	
	template<typename T>
	static void	BubbleSort(T list[],int start,int end){
		
		
		T tmp;
		if(start < end){
			for(size_t i = start; i <= end; ++i)
			{
				for(size_t j = i+1; j <= end; ++j)
				{
					if(list[i]>=list[j]){
					
						tmp=list[i];
						list[i]=list[j];
						list[j]=tmp;
					
					}

				}

			}
			
		}
			
	}
	

	
	
	
}


#endif