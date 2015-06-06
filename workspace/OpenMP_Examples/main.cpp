#include <iostream>
#include <omp.h>

#define USE_OMP
#include "../Examples/util.hpp"

int main() {
    // #pragma omp parallel num_threads(4)
	#pragma omp parallel
	{
		std::cout << "Hello world!" << std::endl;

        omp_set_lock(&lock) ;
        omp_unset_lock(&lock) ;
	}
	return 0;
}
