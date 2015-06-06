#define USE_STD
#include "util.hpp"

// Standard Schleife ohne Abhängigkeiten
void loop() {
	for (unsigned int i = 0; i < 10; ++i) {
        sleep(1.0);
		std::cout << "i = " << i << std::endl;
	}
}

// Abhängigkeiten zwischen Schleifendurchläufen
void loop2() {
    for (unsigned int i = 1; i < 10; ++i) {
        std::cout << i << "+" << (i-1) << " = " << i + (i - 1) << std::endl;
    }
}

// Iteratoren
void loop3() {
    std::vector<unsigned int> list(5);
    for (unsigned int i = 0; i < list.size(); ++i) {
        list[i] = i;
    }

    for (std::vector<unsigned int>::iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << "i = " << *it << std::endl;
    }
}

// Reduce für std-Datentypen
void reduce_sum() {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < 10; ++i) {
		sum += i;
	}

	std::cout << "sum = " << sum << std::endl;
}

class sum_custom {
    unsigned int a;
public:
    sum_custom(int value) : a(value) {}

    sum_custom& operator+=(const sum_custom& other) {
        this->a += other.a;
        return *this;
    }

    sum_custom& operator=(int value) {
        this->a = value;
        return *this;
    }

    friend
    std::ostream& operator<<(std::ostream& os, const sum_custom& sum) {
        return os << sum.a << std::endl;
    }
};

// Eigene Datentypen
void reduce_sum_custom() {
    sum_custom sum(0);
    for (unsigned int i = 0; i < 10; ++i) {
		sum += i;
	}

	std::cout << "sum = " << sum << std::endl;
}

// Aufteilung in unabhängige Sectionen
void section() {
	std::ifstream file1("file1.txt");
	std::string line1;
	std::getline(file1, line1);
	std::cout << "File1: " << line1 << std::endl;

	std::ifstream file2("file2.txt");
	std::string line2;
	std::getline(file2, line2);
	std::cout << "File2: " << line2 << std::endl;
}

// Sortieren
void sort() {
    std::vector<unsigned int> list(5);
    list[0] = 3;
    list[1] = 1;
    list[2] = 0;
    list[3] = 4;
    list[4] = 2;

    // sort

    for (std::vector<unsigned int>::iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << "i = " << *it << std::endl;
    }
}

void lock() {
}

int main(int argc, char* argv[]) {
    bool use_cout = false;
    if (argc > 1) {
        use_cout = true;
    }
    init("std", use_cout);

    RUN(loop);
    RUN(loop2);
    RUN(loop3);
    RUN(reduce_sum);
    RUN(reduce_sum_custom);
    RUN(section);
    RUN(sort);

	std::cout << "Hello world!" << std::endl;
	return 0;
}

/*
Code

schleifen mit sleep/busy wait, damit längere Laufzeit geprüft werden kann
abhängigkeiten zu anderen schleifendurchläufen
sectionen
reduce (pod, eigene klasse)
sortieren (quicksort)
*/
