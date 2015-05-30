#include <iostream>
#include <fstream>

int main() {
    std::ifstream file1("file1.txt");
    std::string line1;
    std::getline(file1, line1);
    std::cout << "File1: " << line1 << std::endl;

    std::ifstream file2("file2.txt");
    std::string line2;
    std::getline(file2, line2);
    std::cout << "File2: " << line2 << std::endl;

	return 0;
}

