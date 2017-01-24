#ifndef COMMAND_H
#define COMMAND_H
#include <mutex>
#include <regex>
#include <string>
#include <iostream>
#include <functional>

typedef std::function<void* (const void* args)> func;


class CCommand {
public:
    const std::string signature;
    const bool have_args;

    void* call(void* args = nullptr);

    CCommand(): have_args(false) { };
    ~CCommand() {};
    CCommand(const std::string signature, const func callback, const bool have_args = false);
private:
    std::mutex access;
    func callback;
};
#endif /* COMMAND_H */
