/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * 2-DIMENSIONAL ARRAY
 *
 * Simulated by 1-dimension array.
 ******************************************************************************/
 
#ifndef __2D_ARRAY_H__
#define __2D_ARRAY_H__
#include <stdint.h>
#include <stdlib.h>

/**
 * 2D Array definition
 */
template <typename T=char>
class Array2D
{
private:
	uint32_t nrow;	// num of rows
	uint32_t ncol;	// num of columns
	T * data;		// the place where the array resides.
public:
	Array2D(uint32_t nrow, uint32_t ncol) {
		this->nrow = nrow;
		this->ncol = ncol;	
		this->data = new T[nrow*ncol];
	};

	inline T& operator() (int row, int col) {
		return this->data[row*ncol + col];
	}

	inline void operator== (T value) {
		for(int i=0; i<ncol*nrow;i++){
			data[i]	 = value;
		}
	}
	
	virtual ~Array2D() {
		delete [] data;
	}
};

#endif //
