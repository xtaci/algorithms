#include "dictionary.h"
#include "hash_table.h"
#include "random.h"
#include <chrono>

using namespace alg;
using namespace std::chrono;

int main(void) {
	
	Dictionary<int, int> dict;

	dict.Add(0, 1);
	dict.Add(1, 2);
	dict.Add(5, 2);
	dict.Add(3, 3);
	dict.Remove(5);
	dict.AddOrUpdate(3, 4);

	for (auto x : dict)
	{
		printf("%d - %d\n", x.Key, x.Value);
	}

	static const uint32_t TEST_LENGTH = 1000000;
	Dictionary<uint32_t, uint32_t> d(TEST_LENGTH);
	HashTable<uint32_t, uint32_t> h(TEST_LENGTH);

	auto t0 = high_resolution_clock::now();

	for (uint32_t i = 0; i < TEST_LENGTH; i++)
	{
		d.AddOrUpdate(alg::LCG(), alg::LCG());
	}

	auto t1 = high_resolution_clock::now();

	for (uint32_t i = 0; i < TEST_LENGTH; i++)
	{
		h[alg::LCG()] = alg::LCG();
	}

	auto t2 = high_resolution_clock::now();

	auto dt0 = duration_cast<milliseconds>(t1 - t0).count();
	auto dt1 = duration_cast<milliseconds>(t2 - t1).count();

	printf("Dictionary: %lld ms, HashTable: %lld ms\n", dt0, dt1);
}
