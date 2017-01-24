#include "command.h"


CCommand::CCommand(const std::string signature, const func callback, const bool have_args):
        signature(signature), callback(callback), have_args(have_args)
{};

void* CCommand::call(void* args) {
    try {
        access.try_lock();
        void* result = have_args ? callback(args): callback(nullptr);
        access.unlock();

        return result;
    }
    catch(const std::exception& ex) {
        access.unlock();
        std::cout << "[ERROR] Command \"" << signature << "\" failed: " << ex.what();
        return (void*) -1;
    }
    catch(...) {
        access.unlock();
        std::cout << "[ERROR] Command \"" << signature << "\" have fatal error.";
        return (void*) -1;
    }
};