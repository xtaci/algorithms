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
struct Array2D
{
	uint32_t nrow;	// num of rows
	uint32_t ncol;	// num of columns
	uintptr_t * data;		// the place where the array resides.
};

/**
 * create a 2-D array of size 'nrow' times 'ncol', an new Array2D struct is
 * returned.
 */
static inline struct Array2D * 
array2d_create(uint32_t nrow, uint32_t ncol)
{
	struct Array2D * arr = (struct Array2D *)malloc(sizeof(struct Array2D));
	
	arr->nrow = nrow;
	arr->ncol = ncol;
	arr->data = (uintptr_t *)malloc(nrow * ncol * sizeof(uintptr_t));

	return arr;
}

/**
 * safely destroy and free array
 */
static inline void 
array2d_destroy(struct Array2D * array)
{
	free(array->data);
	free(array);
}

/**
 * get value from given row and col
 */
static inline uintptr_t
array2d_get(struct Array2D * array, uint32_t row, uint32_t col)
{
	return array->data[array->ncol * row + col];
}

/**
 * set value to [row, col]
 */
static inline void 
array2d_set(struct Array2D * array, uint32_t row, uint32_t col, uintptr_t value)
{
	array->data[array->ncol * row + col] = value;
}

/**
 * set all value to a some value
 */
static inline void
array2d_clear(struct Array2D * array, uintptr_t value)
{
	int i;
	int count = array->nrow * array->ncol;

	for(i=0;i<count;i++) {
		array->data[i] = value;
	}
}

#endif //
