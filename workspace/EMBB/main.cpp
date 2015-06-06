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

int main() {
    embb::tasks::Node::GetInstance();

    //RUN(runfib);
    RUN(RunScan);
    RUN(RunCountIf);

    //embb::tasks::Node& node = embb::tasks::Node::GetInstance();

	return 0;
}
