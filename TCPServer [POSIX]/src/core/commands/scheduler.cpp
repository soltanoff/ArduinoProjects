#include "scheduler.h"

// ====================================================================================================================
// COMMAND FUNCTIONS PROTOTYPES
std::string help(const std::string arg);  // cmd: help
std::string test(const std::string arg);  // cmd: test
std::string store(const std::string arg); // cmd: store <args>
std::string get_all(const std::string arg); // cmd: getall
std::string get_read(const std::string arg); // cmd: get_read
std::string get_unread(const std::string arg); // cmd: get_unread
std::string set_read_all(const std::string arg); // cmd: set_read_all
std::string clear_db(const std::string arg); // cmd: clear_db
// ====================================================================================================================
// COMMAND LIST
std::vector<std::shared_ptr<CCommand>> COMMAND_LIST = {
        std::shared_ptr<CCommand>(new CCommand("help", &help, true)),
        std::shared_ptr<CCommand>(new CCommand("test", &test, true)),
        std::shared_ptr<CCommand>(new CCommand("store", &store, true)),
        std::shared_ptr<CCommand>(new CCommand("get_all", &get_all, false)),
        std::shared_ptr<CCommand>(new CCommand("get_read", &get_read, false)),
        std::shared_ptr<CCommand>(new CCommand("get_unread", &get_unread, false)),
        std::shared_ptr<CCommand>(new CCommand("set_read_all", &set_read_all, false)),
        std::shared_ptr<CCommand>(new CCommand("clear_db", &clear_db, false)),

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
std::string command_scheduler(const std::string command) {
    const std::regex re("(\\w+)\\s*(.*)?\\s*");
    std::smatch result;
    std::string error;

    try {
        if (std::regex_search(command, result, re)) {
            std::string cmd(result.str(1));
            std::string args(result.str(2));

            for (auto it = COMMAND_LIST.begin(); it != COMMAND_LIST.end(); it++) {
                if (cmd.compare((*it)->signature) == 0) {
                    std::cout << "[SERVER] Command execute: "+ cmd << std::endl;
                    return (*it)->call(args);
                }
            }

            error = "Unknown command: "+ command;
            std::cout << "[SERVER] " << error << std::endl;
            return error;
        } else {
            error = "[SERVER] Command string is incorrect: "+ command;
            std::cout << error << std::endl;
            return error;
        }
    }
    catch(std::exception& ex) {
        error = "[ERROR] Command Scheduler failed: ";
        error += ex.what();
        std::cout << error << std::endl;
        return error;
    }
    catch(...) {
        error = "[ERROR] Command Scheduler have fatal error.";
        std::cout << error << std::endl;
        return error;
    }
}
