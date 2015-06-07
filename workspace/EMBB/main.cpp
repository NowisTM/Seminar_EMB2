#include <embb/mtapi/mtapi.h>
#include <embb/base/base.h>
#include <embb/containers/containers.h>
#include <embb/dataflow/dataflow.h>
#include <embb/tasks/node.h>

//#include "src/fib.hpp"
#include "src/scan.hpp"
#include "src/countif.hpp"

#define RUN(fct) std::cout << std::endl << "## " #fct " ##" << std::endl; \
    try { \
        fct(); \
    } catch (embb::base::Exception& e) { \
        std::cout << "## " #fct " exception: " << e.What() << std::endl; \
    } catch (std::exception& e) { \
        std::cout << "## " #fct " exception: " << e.what() << std::endl; \
    } \
    std::cout << "## " #fct " end ##" << std::endl;

int main2() {
	embb::tasks::Node::GetInstance();

	//RUN(runfib);
	//RUN(RunScan);
	//RUN(RunCountIf);

	//embb::tasks::Node& node = embb::tasks::Node::GetInstance();

	return 0;
}

#include <iostream>
#include <vector>
#include <embb/algorithms/algorithms.h>

int main() {
	std::vector<int> range(10);
	for (size_t i = 0; i < range.size(); i++) {
		range[i] = i;
	}

    try {
        embb::tasks::Node::GetInstance();

        int i = 0;
        std::cout << "Range: " << std::endl;
        std::for_each(range.begin(), range.end(), [&i] (int value) {
            std::cout << "\t" << i << " = " << value << std::endl; ++i;
        });

        using embb::algorithms::ForEach;
        ForEach(range.begin(), range.end(),
            [] (int& to_double) { to_double *= 2; });

        i = 0;
        std::cout << "Output ForEach: " << std::endl;
        std::for_each(range.begin(), range.end(), [&i] (int value) {
            std::cout << "\t" << i << " = " << value << std::endl; ++i;
        });

        ForEach(range.begin(), range.end(),
            [] (int& value) { value = 0; });

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
            std::cout << "\t" << i << " = " << value << std::endl; ++i;
        });
    } catch (embb::base::Exception& e) {
        std::cout << "Exception: " << e.What() << std::endl;
    }
}
