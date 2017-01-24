#include "scheduler.h"

// ====================================================================================================================
// COMMAND FUNCTIONS PROTOTYPES
void* foo(const void* arg);  // cmd: test
// ====================================================================================================================
// COMMAND LIST
std::vector<std::shared_ptr<CCommand>> COMMAND_LIST = {
        std::shared_ptr<CCommand>(new CCommand("test", &foo, false))
};
// ====================================================================================================================
// SCHEDULER
/*
 * Возвращает результат исполнения команды если такой имеется.
 * Если результата нет, то return nullptr
 * Ошибки:
 * 1) -1    - серьезная ошибка на стороне сервера
 * 2) 0     - строка команды введена неверно
 * 3) 1     - команда не найдена
 */
void* command_sheduler(const std::string command) {
    const std::regex re("(\\w+)\\s*(\\w+)?\\s*");
    std::smatch result;

    try {
        if (std::regex_search(command, result, re)) {
            std::string cmd(result.str(1));
            std::string args(result.str(2));

            for (auto it = COMMAND_LIST.begin(); it != COMMAND_LIST.end(); it++) {
                if (cmd.compare((*it)->signature) == 0) {
                    std::cout << "[SERVER] Command execute: "+ cmd << std::endl;
                    return (*it)->call((void*)args.c_str());
                }
            }
            std::cout << "[SERVER] Command not found: "+ cmd << std::endl;
            return (void*) 1;
        } else {
            std::cout << "[SERVER] Command string is incorrect: "+ command << std::endl;
            return (void*) 0;
        }
    }
    catch(const std::exception& ex) {
        std::cout << "[ERROR] Command Scheduler failed: " << ex.what();
        return (void*) -1;
    }
    catch(...) {
        std::cout << "[ERROR] Command Scheduler have fatal error.";
        return (void*) -1;
    }
}
