#ifndef _SORT_H_
#define _SORT_H_


#include <iostream>
#include <vector>


using namespace std;

namespace alg{

	template<typename T>
	class SortClass{
	public:
		SortClass(vector<T>& sort_list,bool(*comp)(T,T),void(*_swap)(T&,T&)){
			m_sort_list=&sort_list;
			compre=comp;
			swap=_swap;
		}
	
	
		~SortClass(){
			
		}
		
		//
		//	插入排序法
		//
		void insertSort(){
			int j;
			T temp;
			for(size_t i = 1; i < (*m_sort_list).size(); ++i)
			{
				temp=(*m_sort_list)[i];
				j=i-1;
				while((j>=0) && (compre((*m_sort_list)[j],temp)==true)){
					(*m_sort_list)[j+1] = (*m_sort_list)[j];
					j--;
				}
				(*m_sort_list)[j+1] = temp;
				/* code */
			}
			
		}
		
		
		//
		//	冒泡排序法
		//
		void bubbleSort(){
			
			for(size_t i = 0; i < (*m_sort_list).size(); ++i)
			{
				for(size_t j = i+1; j < (*m_sort_list).size(); ++j)
				{
					if(compre((*m_sort_list)[i],(*m_sort_list)[j])==true){
						
						swap((*m_sort_list)[i],(*m_sort_list)[j]);
						
					}

				}

			}
			
		}
		
	
		//
		//	快速排序
		//
		void quickSort(){
			_quickSort((*m_sort_list),0,(*m_sort_list).size()-1);
		}
		
		
		//
		//	选择排序
		//
		void selectionSort(){
			
			int min_index;

			for(size_t i = 0; i < (*m_sort_list).size()-1; ++i)
			{
				min_index=i;
				for(size_t j = i+1; j < (*m_sort_list).size(); ++j)
				{
					if ( compre((*m_sort_list)[min_index],(*m_sort_list)[j]) == true)
						min_index=j;
					
				}
				
				if (i != min_index)
				{
					swap((*m_sort_list)[min_index],(*m_sort_list)[i]);
					
				}
			}
			
		}
		
		
		//
		//	归并排序
		//
		void mergeSort(){
			
			_mergeSort(1);
			
		}
		
		
		//
		//	堆排序
		//
		void heapSort(){
	
			buildHeap();
			for(int i = (*m_sort_list).size()-1; i > 0; --i)
			{
				swap((*m_sort_list)[0],(*m_sort_list)[i]);
								
				adjHeap(0,i);

			}
		}
		
		
		
		void displaySort(){
			
			for(size_t i = 0; i < (*m_sort_list).size(); ++i)
			{
				cout << (*m_sort_list)[i] << ",";

			}
			cout << endl;

		}
	
	
	
	
	private:
		vector<T> *m_sort_list;
		vector<T> m_merge_list;
		bool (*compre)(T,T);
		void (*swap)(T&,T&);
		
		//
		//	归并排序具体实现,双路归并
		//
		void _mergeSort(int len){

			if(len>(*m_sort_list).size())
				return;
			
			m_merge_list.clear();
			for(size_t i = 0; i < (*m_sort_list).size(); i+=len*2)
			{
				
				int j=i;
				int k=i+len;
				int maxj = ( i+len >= (*m_sort_list).size() ) ? (*m_sort_list).size() : (i+len);
				int maxk = ( i+2*len >= (*m_sort_list).size() ) ? (*m_sort_list).size() : (i+2*len);
				
				while((j<maxj) && (k<maxk) )
				{
					if ( compre((*m_sort_list)[k],(*m_sort_list)[j]))
					{
						m_merge_list.push_back((*m_sort_list)[j]);
						j++;
					}else{
						m_merge_list.push_back((*m_sort_list)[k]);
						k++;
					}
				}
				
				if(j==maxj){
					for(size_t ii = k; ii < maxk; ++ii)
					{
						m_merge_list.push_back((*m_sort_list)[ii]);
					}
				}else
				{
					for(size_t ii = j; ii < maxj; ++ii)
					{
						m_merge_list.push_back((*m_sort_list)[ii]);
					}
				}
				
			}
			
			*m_sort_list= m_merge_list;
			
			
			_mergeSort(len*2);
			
		}
		
		//
		//	堆排序，调整堆
		//
		void adjHeap(int start,int size){
			
			
	
			int left=start*2+1;
			int right=start*2+2;
	
			
			if(  ( compre((*m_sort_list)[start],(*m_sort_list)[left]) == false )  &&left < size){
				
				swap((*m_sort_list)[start],(*m_sort_list)[left]);
				
			
				adjHeap(left,size);
			}
			
			if(  ( compre((*m_sort_list)[start],(*m_sort_list)[right]) == false ) && right < size){
				swap((*m_sort_list)[start],(*m_sort_list)[right]);
				
				
				adjHeap(right,size);
			}	
			
				
			return ;
			
			
		}
		
		//
		//	堆排序，建立堆
		//
		void buildHeap(){
			
			for(int i = ((*m_sort_list).size()-1)/2; i >= 0 ; --i)
			{
				adjHeap(i,(*m_sort_list).size());
			}
			
			
		}
		
		
		//
		//	快速排序具体实现
		//
		void _quickSort(vector<T>& arr,int start,int end){
			
			int i,j;
			i = start;
			j = end;
			if((arr.size()==0))
				return;
			         
			while(i<j){
			      
				while(i<j && compre(arr[j],arr[i])){     
					j--;
				}
				if(i<j){   
					swap(arr[i],arr[j]);
				               
					
				}
				   
				   
				while(i<j&&compre(arr[j],arr[i])){    
					i++;
				}
				if(i<j){   
					swap(arr[i],arr[j]);              
					
				}
			}
					
			if(i-start>1){
				_quickSort(arr,start,i-1);
			}
					
			if(end-j>1){
				_quickSort(arr,j+1,end);
			}
		}

	};


}


#endif