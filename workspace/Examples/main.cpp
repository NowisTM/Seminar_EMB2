#include <algorithm>

#define USE_STD
#include "util.hpp"

// ohne sleep
void loop() {
    for (unsigned int i = 0; i < 10; ++i) {
		std::cout << "i = " << i << std::endl;
	}
}

// Standard Schleife ohne Abhängigkeiten
void loop2() {
	for (unsigned int i = 0; i < 10; ++i) {
        sleep();
		std::cout << "i = " << i << std::endl;
	}
}

// Abhängigkeiten zwischen Schleifendurchläufen
void loop3() {
    std::vector<int> range(10);
    range[0] = 0;

    for (unsigned int i = 1; i < range.size(); ++i) {
        sleep();
        range[i] = range[i - 1] + 1;
    }

    for (unsigned int i = 1; i < range.size(); ++i) {
        std::cout << i << " = " << range[i] << std::endl;
    }
}

// Reduce für std-Datentypen
void reduce_sum() {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < 10; ++i) {
        sleep();
		sum += i;
	}

	std::cout << "sum = " << sum << std::endl;
}

// Eigene Datentypen
void reduce_sum_custom() {
    SumCustom sum(0);
    for (unsigned int i = 0; i < 10; ++i) {
        sleep();
		sum += i;
	}

	std::cout << "sum = " << sum << std::endl;
}

// Aufteilung in unabhängige Sectionen
void section() {
    sleep();
	std::ifstream file1("file1.txt");
	std::string line1;
	std::getline(file1, line1);
	std::cout << "File1: " << line1 << std::endl;

    sleep();
	std::ifstream file2("file2.txt");
	std::string line2;
	std::getline(file2, line2);
	std::cout << "File2: " << line2 << std::endl;
}

struct {
    bool operator()(unsigned int a, unsigned int b)
    {
        sleep();
        return a < b;
    }
} customSort;

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
    std::sort(list.begin(), list.end(), customSort);

    for (std::vector<unsigned int>::iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << "i = " << *it << std::endl;
    }
}

int main(int argc, char* argv[]) {
    bool use_cout = false;
    if (argc > 1) {
        use_cout = true;
    }
    #ifndef FLAG
    init("std", use_cout);
    #else
    init("flag", use_cout);
    #endif

    RUN(loop);
    RUN(loop2);
    RUN(loop3);
    RUN(reduce_sum);
    RUN(reduce_sum_custom);
    RUN(section);
    RUN(sort);

	return 0;
}
