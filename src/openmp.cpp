#include <iostream>
#include <omp.h>

int main() {
	int max = 10;

	#pragma omp parallel for //num_threads(2)
	for (int i = 0; i < max; i++) {
		std::cout << "Done in Thread " 
				  << omp_get_thread_num() 
				  << ", num = " << i << std::endl;
	}

	return 1;
}
