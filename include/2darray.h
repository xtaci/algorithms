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
 
#ifndef ALGO_2D_ARRAY_H__
#define ALGO_2D_ARRAY_H__
#include <stdint.h>
#include <stdlib.h>

namespace alg {
	/**
	 * 2D Array definition
	 */
	template <typename T=char>
		class Array2D {
			private:
				uint32_t NR;		// num of rows
				uint32_t NC;		// num of columns
				T * m_data;			// the place where the array resides.

			public:
				/**
				 * construct an array of size [nrow,col]
				 */
				Array2D(uint32_t nrow, uint32_t ncol) {
					NR = nrow;
					NC = ncol;	
					m_data = new T[nrow*ncol];
				}

				/**
				 * destructor
				 */	
				~Array2D() {
					delete [] m_data;
				}

			private:
				Array2D(const Array2D&);	
				Array2D& operator=(const Array2D&);	

			public:

				/**
				 * return number of rows of this array
				 */
				inline const uint32_t row() const { return NR; }
				/**
				 * return number of columns of this array
				 */
				inline const uint32_t col() const { return NC; }

				/**
				 * return the value by the given (row, col);
				 */
				inline T& operator() (int row, int col) { return this->m_data[row*NC + col]; }
				const inline T& operator() (int row, int col) const { return this->m_data[row*NC + col]; }

				inline T* operator[] (int row) { return &(m_data[row * NC]); }
				inline const T* operator[] (int row) const { return &(m_data[row * NC]); }

				/**
				 * clear the array by a given value
				 */
				void clear(const T & value) {
					for(uint32_t i=0; i<NR*NC;i++){
						m_data[i] = value;
					}
				}
		};
}

#endif //
