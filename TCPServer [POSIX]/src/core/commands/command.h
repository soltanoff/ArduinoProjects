#ifndef COMMAND_H
#define COMMAND_H
/* ================================================================================================================== */
#include <mutex>
#include <regex>
#include <string>
#include <iostream>
#include <functional>
#include "../database/database.h"
#include "../../config/config.h"
/* ================================================================================================================== */
typedef std::function<std::string (const std::string args)> func;


class CCommand {
public:
    const std::string signature;

    std::string call(const std::string args);

    CCommand(): _have_args(false) { };
    ~CCommand() {};
    CCommand(const std::string signature, const func callback, const bool have_args = false);
private:
    const bool _have_args;
    std::mutex _access;

    func _callback;
};
#endif /* COMMAND_H */
