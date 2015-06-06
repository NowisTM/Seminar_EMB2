#include <embb/mtapi/mtapi.h>
#include <embb/base/base.h>
#include <embb/containers/containers.h>
#include <embb/dataflow/dataflow.h>
#include <embb/tasks/node.h>

#define USE_EMBB
#include "../Examples/util.hpp"

void init_embb() {
	embb::tasks::Node::GetInstance();
}

void run() {
	// bla
}

int main(int argc, char* argv[]) {
    bool use_cout = false;
    if (argc > 1) {
        use_cout = true;
    }
    init("embb", use_cout);

    RUN(init_embb);

    RUN(run);

	return 0;
}
