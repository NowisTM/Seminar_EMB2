#include <omp.h>

#define USE_OMP
#include "../Examples/util.hpp"

void run() {
    // #pragma omp parallel num_threads(4)
	#pragma omp parallel
	{
		std::cout << "Hello world!" << std::endl;

        /*omp_set_lock(&lock) ;
        omp_unset_lock(&lock) ;*/
	}
}

int main(int argc, char* argv[]) {
    bool use_cout = false;
    if (argc > 1) {
        use_cout = true;
    }
    init("omp", use_cout);

    RUN(run);
	return 0;
}
