/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * INTEGER -- OF ARBITARY LENGTH
 *
 * Retrieved from: http://en.literateprograms.org/Arbitrary-precision_integer_arithmetic_(C)?oldid=16902
 *
 ******************************************************************************/

#ifndef __INTEGER_H__
#define __INTEGER_H__

#include <stdlib.h>  
#include <stdint.h>
#include <stdbool.h>
#include <string.h>  
#include <limits.h>

typedef uint32_t component_t;
typedef uint64_t double_component_t;

#define MAX_COMPONENT  ((component_t)(-1))
#define COMPONENT_BITS  (sizeof(component_t)*CHAR_BIT)

#define LOG_2_10    3.3219280948873623478703194294894

#define MIN(x,y)  ((x)<(y) ? (x) : (y))
#define MAX(x,y)  ((x)>(y) ? (x) : (y))

typedef struct {
    component_t* c;    /* least-significant word first */
    int num_components;
} integer;

integer create_integer(int components);
void free_integer(integer i);
void set_zero_integer(integer i);
void copy_integer(integer source, integer target);
void add_integer(integer left, integer right, integer result);
void subtract_integer(integer left, integer right, integer result);
void multiply_small_integer(integer left, component_t right, integer result);
void multiply_integer(integer left, integer right, integer result);
int compare_integers(integer left, integer right);
void shift_left_one_integer(integer arg);
void shift_right_one_integer(integer arg);
component_t mod_small_integer(integer left, component_t right);
void mod_integer(integer left, integer right, integer result);
void divide_small_integer(integer left, component_t right, integer result);
bool is_zero_integer(integer x);


inline integer create_integer(int components) {
    integer result;
    result.num_components = components;
    result.c = (component_t*)malloc(sizeof(component_t)*components);
    return result;
}


inline void free_integer(integer i) {
    free(i.c);
}


inline void set_zero_integer(integer i) {
    memset(i.c, 0, sizeof(component_t)*i.num_components);
}


inline bool is_zero_integer(integer x) {
    int i;
    for(i=0; i < x.num_components; i++) {
        if (x.c[i] != 0) return false;
    }
    return true;
}

inline void copy_integer(integer source, integer target) {
    memmove(target.c, source.c,
            sizeof(component_t)*MIN(source.num_components, target.num_components));
    if (target.num_components > source.num_components) {
        memset(target.c + source.num_components, 0,
               sizeof(component_t)*(target.num_components - source.num_components));
    }
}

inline void add_integer(integer left, integer right, integer result) {
    double_component_t carry = 0;
    int i;
    for(i=0; i<left.num_components || i<right.num_components || carry != 0; i++) {
        double_component_t partial_sum = carry;
        carry = 0;
        if (i < left.num_components)  partial_sum += left.c[i];
        if (i < right.num_components) partial_sum += right.c[i];
        if (partial_sum > MAX_COMPONENT) {
            partial_sum &= MAX_COMPONENT;
            carry = 1;
        }
        result.c[i] = (component_t)partial_sum;
    }
    for ( ; i < result.num_components; i++) { result.c[i] = 0; }
}

inline void subtract_integer(integer left, integer right, integer result) {
    int borrow = 0;
    int i;
    for(i=0; i<left.num_components; i++) {
        double_component_t lhs = left.c[i];
        double_component_t rhs = (i < right.num_components) ? right.c[i] : 0;
        if (borrow) {
	    if (lhs <= rhs) {
	        /* leave borrow set to 1 */
	        lhs += (MAX_COMPONENT + 1) - 1;
	    } else {
	        borrow = 0;
	        lhs--;
	    }
	}
        if (lhs < rhs) {
            borrow = 1;
            lhs += MAX_COMPONENT + 1;
        }
        result.c[i] = lhs - rhs;
    }
    for ( ; i < result.num_components; i++) { result.c[i] = 0; }
}

inline void multiply_small_integer(integer left, component_t right, integer result) {
    double_component_t carry = 0;
    int i;
    for(i=0; i<left.num_components || carry != 0; i++) {
        double_component_t partial_sum = carry;
        carry = 0;
        if (i < left.num_components)  partial_sum += left.c[i]*right;
        carry = partial_sum >> COMPONENT_BITS;
        result.c[i] = (component_t)(partial_sum & MAX_COMPONENT);
    }
    for ( ; i < result.num_components; i++) { result.c[i] = 0; }
}

inline void multiply_integer(integer left, integer right, integer result) {
    int i, lidx, ridx;
    double_component_t carry = 0;
    int max_size_no_carry;
    int left_max_component  = left.num_components - 1;
    int right_max_component = right.num_components - 1;
    while(left.c[left_max_component]   == 0) left_max_component--;
    while(right.c[right_max_component] == 0) right_max_component--;
    max_size_no_carry = left_max_component + right_max_component;
    for(i=0; i <= max_size_no_carry || carry != 0; i++) {
        double_component_t partial_sum = carry;
        carry = 0;
        lidx = MIN(i, left_max_component);
        ridx = i - lidx;
        while(lidx >= 0 && ridx <= right_max_component) {
            partial_sum += ((double_component_t)left.c[lidx])*right.c[ridx];
            carry += partial_sum >> COMPONENT_BITS;
            partial_sum &= MAX_COMPONENT;
            lidx--; ridx++;
        }
        result.c[i] = partial_sum;
    }
    for ( ; i < result.num_components; i++) { result.c[i] = 0; }
}

inline int compare_integers(integer left, integer right) {
    int i = MAX(left.num_components - 1, right.num_components - 1);
    for ( ; i >= 0; i--) {
        component_t left_comp =
            (i < left.num_components) ? left.c[i] : 0;
        component_t right_comp =
            (i < right.num_components) ? right.c[i] : 0;
        if (left_comp < right_comp)
            return -1;
        else if (left_comp > right_comp)
            return  1;
    }
    return 0;
}

inline void shift_left_one_integer(integer arg) {
    int i;
    arg.c[arg.num_components - 1] <<= 1;
    for (i = arg.num_components - 2; i >= 0; i--) {
        arg.c[i + 1] |= arg.c[i] >> (COMPONENT_BITS - 1);
        arg.c[i] <<= 1;
    }
}

inline void shift_right_one_integer(integer arg) {
    int i;
    arg.c[0] >>= 1;
    for (i = 1; i < arg.num_components; i++) {
        arg.c[i - 1] |= (arg.c[i] & 1) << (COMPONENT_BITS - 1);
        arg.c[i] >>= 1;
    }
}

inline component_t mod_small_integer(integer left, component_t right) {
    double_component_t mod_two_power = 1;
    double_component_t result = 0;
    int i, bit;
    for(i=0; i<left.num_components; i++) {
        for(bit=0; bit<COMPONENT_BITS; bit++) {
            if ((left.c[i] & (1 << bit)) != 0) {
                result += mod_two_power;
                if (result >= right) {
                    result -= right;
                }
            }
            mod_two_power <<= 1;
            if (mod_two_power >= right) {
                mod_two_power -= right;
            }
        }
    }
    return (component_t)result;
}

inline void mod_integer(integer left, integer right, integer result) {
    integer mod_two_power = create_integer(right.num_components + 1);
    int i, bit;
    set_zero_integer(result);
    set_zero_integer(mod_two_power);
    mod_two_power.c[0] = 1;
    for(i=0; i<left.num_components; i++) {
        for(bit=0; bit<COMPONENT_BITS; bit++) {
            if ((left.c[i] & (1 << bit)) != 0) {
                add_integer(result, mod_two_power, result);
                if (compare_integers(result, right) >= 0) {
                    subtract_integer(result, right, result);
                }
            }
            shift_left_one_integer(mod_two_power);
            if (compare_integers(mod_two_power, right) >= 0) {
                subtract_integer(mod_two_power, right, mod_two_power);
            }
        }
    }
    free_integer(mod_two_power);
}

inline void divide_small_integer(integer left, component_t right, integer result) {
    double_component_t dividend = 0;
    int i;
    for (i = left.num_components - 1; i >= 0; i--) {
        dividend |= left.c[i];
        result.c[i] = dividend/right;
        dividend = (dividend % right) << COMPONENT_BITS;
    }
}

#endif //
