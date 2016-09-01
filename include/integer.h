/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * INTEGER -- OF ARBITARY LENGTH
 *
 * Retrieved from: 
 * http://en.literateprograms.org/Arbitrary-precision_integer_arithmetic_(C)?oldid=16902
 *
 ******************************************************************************/

#ifndef ALGO_INTEGER_H__
#define ALGO_INTEGER_H__

#include <stdlib.h>  
#include <stdint.h>
#include <stdbool.h>
#include <string.h>  
#include <limits.h>
#include <math.h>
#include "generic.h"

namespace alg {
	class Integer {
		private:
			typedef unsigned short component_t;
			typedef unsigned long double_component_t;

#define Max_COMPONENT  ((component_t)(-1))
#define COMPONENT_BITS  (sizeof(component_t)*CHAR_BIT)

#define LOG_2_10    3.3219280948873623478703194294894

			component_t* c;    /* least-significant word first */
			int num_components;

		public:
			Integer(int components) {
				num_components = components;
				c = new component_t[components];
				memset(c, 0, sizeof(component_t)*num_components);
			}

			Integer(const Integer & rhs) {
				num_components = rhs.size();
				c = new component_t[num_components];
				memcpy(c, rhs.components(), num_components*sizeof(component_t));
			}

			~Integer() {
				delete [] c;
			}

			inline const component_t & operator[] (int i) const { return c[i]; }
			inline component_t & operator[] (int i) { return c[i]; }

			inline const component_t * components() const { return c; } 
			inline uint32_t size() const { return num_components; }

			static const Integer from_string(const char* s) {
				Integer result((int)ceil(LOG_2_10*strlen(s)/COMPONENT_BITS));
				Integer digit(1);

				int i;
				for (i = 0; s[i] != '\0'; i++) {
					result = result*10;
					digit[0] = s[i] - '0';
					result = result + digit;
				}

				return result;
			}

			char * to_string() const {
				Integer x = (*this);
				int i, result_len;
				char* result = new char[(int)ceil(COMPONENT_BITS*size()/LOG_2_10) + 2];

				Integer ten(1);
				ten[0] = 10;

				if (x.is_zero()) {
					strcpy(result, "0");
				} else {
					for (i = 0; !x.is_zero(); i++) {
						result[i] = (char)(x%10) + '0';
						x=x/10;
					}
					result[i] = '\0';
				}

				result_len = strlen(result);
				for(i=0; i < result_len/2; i++) {
					char temp = result[i];
					result[i] = result[result_len - i - 1];
					result[result_len - i - 1] = temp;
				}

				return result;
			}

			bool is_zero() {
				uint32_t i;
				for(i=0; i < size(); i++) {
					if ((*this)[i] != 0) return false;
				}
				return true;
			}

			// Integer Assignment
			Integer & operator= (const Integer & source)
			{
				memmove(c, source.components(), sizeof(component_t)*Min(source.size(), size()));

				if (size() > source.size()) {
					memset(c + source.size(), 0, sizeof(component_t)*(size() - source.size()));
				}

				return (*this);
			}

			const Integer operator+ (const Integer & rhs) {
				Integer result(Max(size(), rhs.size())+1);

				double_component_t carry = 0;
				uint32_t i;
				for(i=0; i<size() || i<rhs.size() || carry != 0; i++) {
					double_component_t partial_sum = carry;
					carry = 0;
					if (i < size())  partial_sum += (*this)[i];
					if (i < rhs.size()) partial_sum += rhs[i];
					if (partial_sum > Max_COMPONENT) {
						partial_sum &= Max_COMPONENT;
						carry = 1;
					}
					result[i] = (component_t)partial_sum;
				}
				for ( ; i < result.size(); i++) { result[i] = 0; }

				return result;
			}

			const Integer operator- (const Integer & right) {
				Integer result(Max(size(), right.size()));

				int borrow = 0;
				uint32_t i;
				for(i=0; i<size(); i++) {
					double_component_t lhs = (*this)[i];
					double_component_t rhs = (i < right.size()) ? right[i] : 0;
					if (borrow) {
						if (lhs <= rhs) {
							/* leave borrow set to 1 */
							lhs += (Max_COMPONENT + 1) - 1;
						} else {
							borrow = 0;
							lhs--;
						}
					}
					if (lhs < rhs) {
						borrow = 1;
						lhs += Max_COMPONENT + 1;
					}
					result[i] = lhs - rhs;
				}
				for ( ; i < result.size(); i++) { result[i] = 0; }

				return result;
			}

			const Integer operator* (const component_t & rhs) {
				Integer result(size()+1);

				double_component_t carry = 0;
				uint32_t i;
				for(i=0; i<size() || carry != 0; i++) {
					double_component_t partial_sum = carry;
					carry = 0;
					if (i < size())  partial_sum += (*this)[i]*rhs;
					carry = partial_sum >> COMPONENT_BITS;
					result[i] = (component_t)(partial_sum & Max_COMPONENT);
				}
				return result;
			}

			const Integer operator* (const Integer & rhs) {
				Integer result(Max(size(), rhs.size())*2);

				uint32_t i, lidx, ridx;
				double_component_t carry = 0;
				uint32_t max_size_no_carry;
				uint32_t left_max_component  = size() - 1;
				uint32_t right_max_component = rhs.size() - 1;
				while((*this)[left_max_component] == 0) left_max_component--;
				while(rhs[right_max_component] == 0) right_max_component--;
				max_size_no_carry = left_max_component + right_max_component;
				for(i=0; i <= max_size_no_carry || carry != 0; i++) {
					double_component_t partial_sum = carry;
					carry = 0;
					lidx = Min(i, left_max_component);
					ridx = i - lidx;
					while(lidx >= 0 && ridx <= right_max_component) {
						partial_sum += ((double_component_t)(*this)[lidx])*rhs[ridx];
						carry += partial_sum >> COMPONENT_BITS;
						partial_sum &= Max_COMPONENT;
						lidx--; ridx++;
					}
					result[i] = partial_sum;
				}
				for ( ; i < result.size(); i++) { result[i] = 0; }
				return result;
			}

			const Integer operator/ (component_t rhs) {
				Integer result(size());
				double_component_t dividend = 0;
				int i;
				for (i = size() - 1; i >= 0; i--) {
					dividend |= (*this)[i];
					result[i] = dividend/rhs;
					dividend = (dividend % rhs) << COMPONENT_BITS;
				}

				return result;
			}

			component_t operator% (component_t right) {
				double_component_t mod_two_power = 1;
				double_component_t result = 0;
				uint32_t i, bit;
				for(i=0; i<size(); i++) {
					for(bit=0; bit<COMPONENT_BITS; bit++) {
						if (((*this)[i] & (1 << bit)) != 0) {
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

			const Integer operator% (const Integer & rhs) {
				Integer result = rhs;
				Integer mod_two_power(rhs.size() + 1);

				uint32_t i, bit;
				mod_two_power[0] = 1;
				for(i=0; i<size(); i++) {
					for(bit=0; bit<COMPONENT_BITS; bit++) {
						if (((*this)[i] & (1 << bit)) != 0) {
							result = mod_two_power+result;
							if (result.compare(rhs) >= 0) {
								result = result - rhs;
							}
						}
						mod_two_power.shift_left_one_integer();
						if (mod_two_power.compare(rhs) >= 0) {
							mod_two_power = mod_two_power - rhs;
						}
					}
				}

				return result;
			}

			int compare(const Integer & rhs) {
				uint32_t i = Max(size() - 1, rhs.size() - 1);
				for ( ; i >= 0; i--) {
					component_t left_comp =
						(i < size()) ? (*this)[i] : 0;
					component_t right_comp =
						(i < rhs.size()) ? rhs[i] : 0;
					if (left_comp < right_comp)
						return -1;
					else if (left_comp > right_comp)
						return  1;
				}
				return 0;
			}

		private:
			void shift_left_one_integer() {
				uint32_t i;
				(*this)[size() - 1] <<= 1;
				for (i = size() - 2; i >= 0; i--) {
					(*this)[i + 1] |= (*this)[i] >> (COMPONENT_BITS - 1);
					(*this)[i] <<= 1;
				}
			}

			void shift_right_one_integer() {
				uint32_t i;
				(*this)[0] >>= 1;
				for (i = 1; i < size(); i++) {
					(*this)[i - 1] |= ((*this)[i] & 1) << (COMPONENT_BITS - 1);
					(*this)[i] >>= 1;
				}
			}
	};
}

#endif //
