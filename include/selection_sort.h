#ifndef _selection_sort_h_
#define _selection_sort_h_



namespace aglo{
	
	template<typename T>
	static void SelectionSort(T list[],int start,int end){
	
		int min_index;
		T tmp;

		if(start < end){
			
			for(size_t i = start; i <= end-1; ++i)
			{
				min_index=i;
				for(size_t j = i+1; j <= end; ++j)
				{
					if ( list[i] >= list[j])
						min_index=j;
			
				}
		
				if (i != min_index)
				{
					tmp=list[i];
					list[i]=list[min_index];
					list[min_index]=tmp;
			
				}
			}
			
		}

		
	
	}

}




#endif