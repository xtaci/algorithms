#include <disjoint-set.h>
#include <stdio.h>
#include <iostream>

int main(void) {
	alg::Set<int> s1;
	alg::Set<int> s2;
	alg::MakeSet(&s1);
	alg::MakeSet(&s2);

	printf("before:\n");
	std::cout<< alg::FindSet(&s1) << std::endl;
	std::cout<< alg::FindSet(&s2) << std::endl;

	printf("after:\n");
	alg::Union(&s1, &s2);
	std::cout<< alg::FindSet(&s1) << std::endl;
	std::cout<< alg::FindSet(&s2) << std::endl;
}
