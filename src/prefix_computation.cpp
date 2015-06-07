#include <iostream>
#include <vector>

/*
int main() {
	std::vector<unsigned int> range(11);
	range[0] = 0;

	for (unsigned int i = 1; i < range.size(); ++i) {
		range[i] = range[i - 1] + 1;
	}
}
*/

int main() {
	std::vector<unsigned int> range(11);
	range[0] = 0;

	for (unsigned int i = 1; i < range.size(); ++i) {
		range[i] = range[i - 1] + 1;
	}	
	
	for (unsigned int i = 0; i < range.size(); ++i) {
		std::cout << i << " = " << range[i] << std::endl;
	}
}

