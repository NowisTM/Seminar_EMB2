#include <embb/mtapi/mtapi.h>
#include <embb/base/base.h>
#include <embb/containers/containers.h>
#include <embb/dataflow/dataflow.h>
#include <embb/tasks/node.h>
#include <embb/algorithms/algorithms.h>

#include <mutex>

#define USE_EMBB
#include "../Examples/util.hpp"

void init_embb() {
	embb::tasks::Node::GetInstance();
}

void loop() {
	std::vector<int> range(10);
	initVector(range);

	using embb::algorithms::ForEach;
	ForEach(range.begin(), range.end(), [] (int value) {
		sleep();
		std::cout << value << std::endl;
	});
}

void loop2() {
	std::vector<int> range(10), output_range(10);
	initVector(range, 0);
	initVector(output_range, 0);

	using embb::algorithms::Scan;
	Scan(range.begin(), range.end(), output_range.begin(),
		 0, std::plus<int>(), [] (int value) { sleep(); return ++value; });

    for (unsigned int i = 0; i < output_range.size(); ++i) {
        std::cout << i << " = " << output_range[i] << std::endl;
    }
}

// Reduce für std-Datentypen
void reduce_sum() {
	unsigned int sum = 0;
	std::vector<int> range(10);
	initVector(range);

	using embb::algorithms::Reduce;
	sum = Reduce(range.begin(), range.end(), 0, [] (const unsigned int& a, const unsigned int& b) {
		sleep();
		return a + b;
	});

	std::cout << "sum = " << sum << std::endl;
}

// Eigene Datentypen
void reduce_sum_custom() {
	SumCustom sum = 0;
	std::vector<SumCustom> range(10);
	initVector(range);

	using embb::algorithms::Reduce;
	sum = Reduce(range.begin(), range.end(), SumCustom(), [] (const SumCustom & a, const SumCustom & b) {
		sleep();
		return a + b;
	});

	std::cout << "sum = " << sum << std::endl;
}

void reduce_with_calculation() {
	std::vector<int> range(10);
	initVector(range);

	using embb::algorithms::Reduce;
	int sum = Reduce(range.begin(), range.end(),
					 0, std::plus<int>(),
	[](const int& value) {
		sleep();
		return value * 2;
	});

	std::cout << "sum = " << sum << std::endl;
}

void section1() {
	sleep();
	std::ifstream file1("file1.txt");
	std::string line1;
	std::getline(file1, line1);
	std::cout << "File1: " << line1 << std::endl;
}

void section2() {
	sleep();
	std::ifstream file2("file2.txt");
	std::string line2;
	std::getline(file2, line2);
	std::cout << "File2: " << line2 << std::endl;
}

// Aufteilung in unabhängige Sectionen
void section() {
	using embb::algorithms::Invoke;
	Invoke(section1, section2);
}

// Sortieren
void sort() {
	std::vector<unsigned int> list(8);
	list[0] = 3;
	list[1] = 1;
	list[2] = 7;
	list[3] = 5;
	list[4] = 2;
	list[5] = 0;
	list[6] = 4;
	list[7] = 6;

	// sort
	using embb::algorithms::QuickSort;
	QuickSort(list.begin(), list.end(), [] (const unsigned int& a, const unsigned int& b) {
		sleep();
		return a < b;
	});

	for (std::vector<unsigned int>::iterator it = list.begin(); it != list.end(); ++it) {
		std::cout << "i = " << *it << std::endl;
	}
}

int main(int argc, char* argv[]) {
	bool use_cout = false;
	if (argc > 1) {
		use_cout = true;
	}
	init("embb", use_cout);
	init_embb();

	RUN(loop);
	RUN(loop2);
	RUN(reduce_sum);
	RUN(reduce_sum_custom);
	RUN(section);
	RUN(sort);

	return 0;
}
