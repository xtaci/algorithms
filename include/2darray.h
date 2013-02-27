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

namespace alg
{
	/**
	 * 2D Array definition
	 */
	template <typename T=char>
	class Array2D
	{
	private:
		uint32_t NR;		// num of rows
		uint32_t NC;		// num of columns
		T * data;			// the place where the array resides.
	public:
		// construct an array of size [nrow,col]
		Array2D(uint32_t nrow, uint32_t ncol) {
			this->NR = nrow;
			this->NC = ncol;	
			this->data = new T[nrow*ncol];
		};

		const uint32_t row() const { return NR; }
		const uint32_t col() const { return NC; }

		inline T& operator() (int row, int col) { return this->data[row*NC + col]; }
		const inline T& operator() (int row, int col) const { return this->data[row*NC + col]; }

		void clear(const T & value) {
			for(uint32_t i=0; i<NR*NC;i++){
				data[i] = value;
			}
		}
		
		virtual ~Array2D() {
			delete [] data;
		}
	};
}

#endif //
