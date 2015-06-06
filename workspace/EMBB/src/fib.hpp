#define fib_HPP
#ifndef fib_HPP
#define fib_HPP

#include <iostream>
#include <sstream>
#include <embb/tasks/tasks.h>

#define MTAPI_CHECK_STATUS(status) \
    if (MTAPI_SUCCESS != status) { \
        std::stringstream ss;\
        ss << "error " << status << " in " << __FILE__ << ":" << __LINE__ << std::endl; \
        throw embb::mtapi::StatusException(ss.str().c_str()); \
        exit(status); \
    }

void fibonacciActionFunction (int n, int* result, embb::tasks::TaskContext& task_context) {
    embb::tasks::Node& node = embb::tasks::Node::GetInstance();
    if (n < 2) {
        *result = n;
    } else {
        int a = n - 1;
        int x;

        embb::tasks::Task task = node.Spawn(
            embb::base::Bind(
                embb::base::MakeFunction(fibonacciActionFunction),
                a,
                &x,
                embb::base::Placeholder::_1
            )
        );

        int b = n - 2;
        int y;
        fibonacciActionFunction(b, &y, task_context);

        mtapi_status_t status = task.Wait(MTAPI_INFINITE);
        MTAPI_CHECK_STATUS(status);

        *result = x + y;
    }
}

/*void fibonacciActionFunction (
        const void* args, mtapi_size_t arg_size, void* result_buffer,
        mtapi_size_t result_buffer_size,
        const void* node_local_data, mtapi_size_t node_local_data_size,
        mtapi_task_context_t* task_context) {

    // check size of arguments
    mtapi_status_t status;
    if (arg_size != sizeof(int)) {
        std::cout << "Wrong size of arguments" << std::endl;
        mtapi_context_status_set(task_context, MTAPI_ERR_ARG_SIZE, &status);
        MTAPI_CHECK_STATUS(status);
        return;
    }

    int* result = MTAPI_NULL;
    if (result_buffer == MTAPI_NULL) {
        mtapi_context_status_set(
            task_context, MTAPI_ERR_RESULT_SIZE, &status);
        MTAPI_CHECK_STATUS(status);
    } else {
        if (result_buffer_size == sizeof(int)) {
            result = (int*)result_buffer;
        } else {
            std::cout << "wrong size of result buffer" << std::endl;
            mtapi_context_status_set(
                task_context, MTAPI_ERR_RESULT_SIZE, &status);
            MTAPI_CHECK_STATUS(status);
            return;
        }
    }

    // cast argument to the desired type
    int n = *(int*)args;
    if (n < 2) {
        *result = n;
    } else {
        int a = n - 1;
        int x;
        embb::mtapi::Task task = node.Start(fibonacciJob, &a, &x);

        int b = n - 2;
        int y;
        fibonacciActionFunction(
            &b, sizeof(int),
            &y, sizeof(int),
            MTAPI_NULL, 0,
            task_context);

        mtapi_status_t status = task.Wait(MTAPI_INFINITE);
        if (status != MTAPI_SUCCESS) {
            std::cout << "task failed with error: " << status << std::endl << std::endl;
            exit(status);
        }

        *result = x + y;
    }
}*/

int fib(int n) {
    int x, y;
    if (n < 2) {
        return n;
    } else {
        x = fib(n - 1);
        y = fib(n - 2);
        return x + y;
    }
}

/*int fibonacci(int n) {
    mtapi_status_t status;

    mtapi_node_attributes_t node_attr;
    mtapi_nodeattr_init(&node_attr, &status);
    MTAPI_CHECK_STATUS(status);

    mtapi_nodeattr_set(
        &node_attr, MTAPI_NODE_TYPE,
        MTAPI_ATTRIBUTE_VALUE(MTAPI_NODE_TYPE_SMP),
        MTAPI_ATTRIBUTE_POINTER_AS_VALUE,
        &status);
    MTAPI_CHECK_STATUS(status);

    mtapi_info_t info;
    mtapi_initialize(
        THIS_DOMAIN_ID, THIS_NODE_ID,
        &node_attr, &info, &status);
    MTAPI_CHECK_STATUS(status);

    mtapi_action_hndl_t fibonacciAction;
    fibonacciAction = mtapi_action_create(
        FIBONACCI_JOB,
        (fibonacciActionFunction),
        MTAPI_NULL,
        0,
        MTAPI_DEFAULT_ACTION_ATTRIBUTES,
        &status
    );
    MTAPI_CHECK_STATUS(status);

    mtapi_task_hndl_t task;
    fibonacciJob = mtapi_job_get(FIBONACCI_JOB, THIS_DOMAIN_ID, &status);
    MTAPI_CHECK_STATUS(status);

    int result;
    task = mtapi_task_start(
        MTAPI_TASK_ID_NONE,
        fibonacciJob,
        (void*)&n;
        sizeof(int),
        (void*)&result,
        sizeof(int),
        MTAPI_DEFAULT_TASK_ATTRIBUTES,
        MTAPI_GROUP_NONE,
        &status
    );
    MTAPI_CHECK_STATUS(status);

    mtapi_action_delete(fibonacciAction, 100, &status);
    MTAPI_CHECK_STATUS(status);

    mtapi_finalize(&status);
    MTAPI_CHECK_STATUS(&status);

    return fib(n);
}*/

int fibonacci(int n) {
    embb::tasks::Node& node = embb::tasks::Node::GetInstance();

    int result;
    embb::tasks::Task task = node.Spawn(
        embb::base::Bind(
            embb::base::MakeFunction(fibonacciActionFunction),
            n,
            &result,
            embb::base::Placeholder::_1
        )
    );

    mtapi_status_t status = task.Wait(MTAPI_INFINITE);
    MTAPI_CHECK_STATUS(status);

    return result;
}

int runfib() {
    EMBB_TRY {
        int result = fibonacci(6);
        std::cout << "result: " << result << std::endl;
    } EMBB_CATCH(embb::mtapi::StatusException& e) {
        std::cout << "MTAPI error occured: " << e.what() << std::endl;
    }
	return 0;
}


#endif // fib_HPP
