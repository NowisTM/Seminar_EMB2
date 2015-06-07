#include <omp.h>

#define USE_OMP
#include "../Examples/util.hpp"

//export OMP_NUM_THREADS=4

void loop() {
	#pragma omp parallel for
	for (unsigned int i = 0; i < 10; ++i) {
		std::cout << "i = " << i << std::endl;
	}
}

void loop2() {
	#pragma omp parallel for
	for (unsigned int i = 0; i < 10; ++i) {
		sleep();
		std::cout << "i = " << i << std::endl;
	}
}

// Funktioniert nicht, weil Schleife in Teile aufgeteilt wird
void loop3() {
	std::vector<int> range(10);
	range[0] = 0;

	#pragma omp parallel for
	for (unsigned int i = 1; i < range.size(); ++i) {
		sleep();
		range[i] = range[i - 1] + 1;
	}

	for (unsigned int i = 1; i < range.size(); ++i) {
		std::cout << i << " = " << range[i] << std::endl;
	}
}

void reduce_sum() {
	unsigned int sum = 0;

	#pragma omp parallel for reduction(+:sum)
	for (unsigned int i = 0; i < 10; ++i) {
		sleep();
		sum += i;
	}

	std::cout << "sum = " << sum << std::endl;
}

void reduce_sum_custom() {
	SumCustom sum(0);

	#pragma omp parallel for
	for (unsigned int i = 0; i < 10; ++i) {
		sleep();

		#pragma omp critical
		sum += i;
	}

	std::cout << "sum = " << sum << std::endl;
}

void section() {
	#pragma omp parallel sections
	{
		#pragma omp section
		{
		    sleep();
			std::ifstream file1("file1.txt");
			std::string line1;
			std::getline(file1, line1);
			std::cout << "File1: " << line1 << std::endl;
		}

		#pragma omp section
		{
		    sleep();
			std::ifstream file2("file2.txt");
			std::string line2;
			std::getline(file2, line2);
			std::cout << "File2: " << line2 << std::endl;
		}
	}
}

void sort() {
	std::vector<unsigned int> vec(8);
	unsigned int* list = &vec[0];
	vec[0] = 3;
	vec[1] = 1;
	vec[2] = 7;
	vec[3] = 5;
	vec[4] = 2;
	vec[5] = 0;
	vec[6] = 4;
	vec[7] = 6;

	auto customLess = [] (const void* a, const void* b) -> int { sleep(); return *(int*)a -* (int*)b; };

	#pragma omp parallel
	{
		int size = vec.size() / omp_get_num_threads();;
		int begin = 0 + size * omp_get_thread_num();

		qsort(&list[begin], size, sizeof(unsigned int), customLess);
	}

	qsort(list, vec.size(), sizeof(unsigned int), customLess);

	for (std::vector<unsigned int>::iterator it = vec.begin(); it != vec.end(); ++it) {
		std::cout << "i = " << *it << std::endl;
	}
}

void lock() {
	int a = 0;

	#pragma omp parallel firstprivate(a) num_threads(4)
	{
		std::cout << "a = " << a << std::endl;
		++a;
	}
}

void lock2() {
	omp_lock_t writeLock;
    omp_init_lock(&writeLock);

	#pragma omp parallel for
	for (int i = 0; i < 10; ++i) {
		sleep();

		omp_set_lock(&writeLock);
		std::cout << "i = " << i << " + a bit long name" << std::endl;
		omp_unset_lock(&writeLock);
	}

    omp_destroy_lock(&writeLock);
}

int main(int argc, char* argv[]) {
	bool use_cout = false;
	if (argc > 1) {
		use_cout = true;
	}
	init("omp", use_cout);

	RUN(loop);
	RUN(loop2);
	RUN(loop3);
	RUN(reduce_sum);
	RUN(reduce_sum_custom);
	RUN(section);
	RUN(sort);

	return 0;
}
