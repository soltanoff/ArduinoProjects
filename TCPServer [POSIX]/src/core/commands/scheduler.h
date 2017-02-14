#ifndef SCHEDULER_H
#define SCHEDULER_H
/* ================================================================================================================== */
#include "../../config/config.h"
#include <regex>
#include <functional>
#include <vector>
#include <map>
#include <list>
/* ================================================================================================================== */
enum class COMMANDS : std::uint32_t {
    unknown=0,
    help,
    test,
    store,
    get_all,
    get_read,
    get_unread,
    set_read_all,
    clear_db
};
/* ================================================================================================================== */


class Scheduler {
public:
    typedef std::function<void(std::vector<std::uint8_t>, SOCKET)> ResultCallback;
    typedef std::function<void(std::vector<std::uint8_t>, ResultCallback, SOCKET)> Func;

    static bool execute_command(const std::uint32_t& cmd_code, const std::string& args, SOCKET& s);
    static int schedule(const std::vector<uint8_t> &data, SOCKET s, const bool& is_gsm);
    static void bind(COMMANDS cmd, Func&& callback, ResultCallback&& result_cb);
private:
    static std::map< std::uint32_t, std::list< std::pair<Func, ResultCallback> > > _callbacks_map;
};

#endif /* SCHEDULER_H */
