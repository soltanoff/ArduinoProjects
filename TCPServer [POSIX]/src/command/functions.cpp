#include "scheduler.h"

// ====================================================================================================================
// COMMAND FUNCTIONS
// cmd: test
void* foo(const void* arg) {
    if (arg == nullptr)
        std::cout << "foo() executed. arg = nullptr :)" << std::endl;
    else
        std::cout << "foo() executed. arg = " << (char*)arg << std::endl;

    return nullptr;
}