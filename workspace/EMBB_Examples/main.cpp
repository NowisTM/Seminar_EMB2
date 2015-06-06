#include <iostream>
#include <string>

#include <embb/mtapi/mtapi.h>
#include <embb/base/base.h>
#include <embb/containers/containers.h>
#include <embb/dataflow/dataflow.h>
#include <embb/tasks/node.h>

#define USE_EMBB
#include "../Examples/util.hpp"

void init() {
	embb::tasks::Node::GetInstance();
}

void run() {
	// bla
}

int main() {
    RUN(init);

    RUN(run);

	return 0;
}
