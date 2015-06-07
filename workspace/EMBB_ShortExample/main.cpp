#include <iostream>
#include <vector>
#include <embb/algorithms/algorithms.h>

void loop1() {
	std::vector<int> range(10);
	for (size_t i = 0; i < range.size(); i++) {
		range[i] = i;
	}

	std::cout << "Parallel " << std::endl;
	using embb::algorithms::ForEach;
	ForEach(range.begin(), range.end(), [] (int value) {
		std::cout << "\t" << value << std::endl;
	});
}

void loop2() {
	std::vector<int> range(10);
	for (size_t i = 0; i < range.size(); i++) {
		range[i] = i;
	}

	int i = 0;
	std::cout << "Range: " << std::endl;
	std::for_each(range.begin(), range.end(), [&i] (int value) {
		std::cout << "\t" << i << " = " << value << std::endl;
		++i;
	});

	using embb::algorithms::ForEach;
	ForEach(range.begin(), range.end(),
	[] (int& to_double) {
		to_double *= 2;
	});

	i = 0;
	std::cout << "Output ForEach: " << std::endl;
	std::for_each(range.begin(), range.end(), [&i] (int value) {
		std::cout << "\t" << i << " = " << value << std::endl;
		++i;
	});

	ForEach(range.begin(), range.end(),
	[] (int& value) {
		value = 0;
	});

	std::vector<int> output(range.size());

	using embb::algorithms::Zip;
	using embb::algorithms::ZipPair;
	ForEach(Zip(range.begin(), output.begin()),
			Zip(range.end(), output.end()),
	[] (ZipPair<int&, int&> pair) {
		pair.Second() = pair.First() * 2;
	});

	i = 0;
	std::cout << "Output ForEach-Zip: " << std::endl;
	std::for_each(output.begin(), output.end(), [&i] (int value) {
		std::cout << "\t" << i << " = " << value << std::endl;
		++i;
	});
}

int main() {
	try {
		embb::tasks::Node::GetInstance();

		loop1();
		//loop2();
	} catch (embb::base::Exception& e) {
		std::cout << "Exception: " << e.What() << std::endl;
	}
}
