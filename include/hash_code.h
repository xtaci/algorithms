#ifndef ALGO_HASH_CODE_H__
#define ALGO_HASH_CODE_H__
#include <string.h>
#include "hash_string.h"
namespace alg {
	/**
	 * default compare funcs
	 */
	template<typename T> 
	struct hash_code {
		uint32_t operator()(T) {
			printf("must provide a hash function for _Key\n");
			return 0;
		}
	};

	template<>
	struct hash_code<const char *> {
		uint32_t operator()(const char* value) {
			return hash_fnv1a(value, strlen(value));
		}
	};

	template<>
	struct hash_code<uint32_t> {
		uint32_t operator()(uint32_t value) {
			return value;
		}
	};

	template<>
	struct hash_code<int32_t> {
		uint32_t operator()(int32_t value) {
			return (uint32_t)value;
		}
	};
}
#endif //
