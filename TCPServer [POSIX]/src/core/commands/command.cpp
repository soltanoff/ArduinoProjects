#include "command.h"


CCommand::CCommand(const std::string signature, const func callback, const bool have_args):
        signature(signature), _callback(callback), _have_args(have_args)
{ };

std::string CCommand::call(const std::string args) {
    try {
        _access.try_lock();
        std::string result = _have_args ? _callback(args): _callback("");
        _access.unlock();

        return result;
    }
    catch(const std::exception& ex) {
        _access.unlock();

        std::string error = "[ERROR] Command \"" + signature + "\" failed: " + ex.what();
        std::cout << error;
        return error;
    }
    catch(...) {
        _access.unlock();
        std::string error = "[ERROR] Command \"" + signature + "\" have fatal error.";
        std::cout << error;
        return error;
    }
};
