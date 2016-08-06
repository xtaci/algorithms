#include <iostream>
#include "random.h"

int main(void) {
	std::cout <<"generate random numbers\n";
	for (int i=0;i<100;i++) {
		std::cout<<alg::LCG()<<"\n";
	}
}
