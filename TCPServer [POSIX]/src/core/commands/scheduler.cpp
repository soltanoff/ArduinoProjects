#include "scheduler.h"


bool Scheduler::execute_command(const std::uint32_t& cmd_code, const std::string& args, SOCKET& s) {
    std::uint32_t int_code = cmd_code;
    auto callbacks = _callbacks_map.find(int_code);
    if (callbacks != _callbacks_map.end()) {
        for (auto func_pair: callbacks->second) {
            auto d = std::vector<std::uint8_t>(args.begin(), args.end());
            func_pair.first(std::move(d), func_pair.second, s);
        }
        return 1;
    } else
        return 0;
}

int Scheduler::schedule(const std::vector<uint8_t> &data, SOCKET s, const bool& is_gsm) {
    static std::regex re("(\\w+)\\s*(.*)?\\s*");
    /*
    struct S
    {
        char h;
        int a;
        float b;
        double c;
    };

    S s;
    COMMANDS fgq;

    std::vector<std::uint8_t> o(sizeof(COMMANDS) + sizeof(S));
    memcpy(o.data(), &fgq, sizeof(COMMANDS));
    memcpy(o.data() + sizeof(COMMANDS), &s, sizeof(S));

    auto data_ptr = data.data();

    memcpy(&fgq, data.data(), sizeof(COMMANDS));
    data_ptr += sizeof(COMMANDS);
    */
    try
    {
        std::string command(data.begin(), data.end());

        if (command == "close") {
            return -1;
        }

        if (not is_gsm) {
            std::smatch result;
            if (std::regex_search(command, result, re)) {
                std::string cmd(result.str(1));
                std::string args = result.str(2);
                // ============================ ==============
                // Command selector
                COMMANDS cmd_code;
                if (cmd == "help")
                    cmd_code = COMMANDS::help;
                else if (cmd == "store")
                    cmd_code = COMMANDS::store;
                else if (cmd == "get_all")
                    cmd_code = COMMANDS::get_all;
                else if (cmd == "get_read")
                    cmd_code = COMMANDS::get_read;
                else if (cmd == "get_unread")
                    cmd_code = COMMANDS::get_unread;
                else if (cmd == "set_read_all")
                    cmd_code = COMMANDS::set_read_all;
                else if (cmd == "clear_db")
                    cmd_code = COMMANDS::clear_db;
                else
                    cmd_code = COMMANDS::unknown;

                return Scheduler::execute_command((std::uint32_t) cmd_code, args, s);
            } else return 0;
        }
        else {
            return Scheduler::execute_command((std::uint32_t) COMMANDS::store, command, s);
        }
    }
    catch(...) {
        std::cout << "[SERVER] Fatal error in Schedule. " << std::endl;
    }
    return 0;
}

void Scheduler::bind(COMMANDS cmd, Func&& callback, ResultCallback&& result_cb) {
    auto callbacks = _callbacks_map.find((std::uint32_t) cmd);
    if(callbacks == _callbacks_map.end())
        _callbacks_map[(std::uint32_t)cmd].emplace_back(std::make_pair(callback, result_cb));
}

std::map<std::uint32_t, std::list<std::pair<Scheduler::Func, Scheduler::ResultCallback>> > Scheduler::_callbacks_map = {};
