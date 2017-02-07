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
    clear_db,
    shutdown
};
/* ================================================================================================================== */
// extern std::vector<std::shared_ptr<CCommand>> COMMAND_LIST;
// std::string command_scheduler(const std::string command);


class Scheduler {
public:
    typedef std::function<void(std::vector<std::uint8_t>, std::function< void(std::vector<std::uint8_t>) >)> Func;
    typedef std::function<void(std::vector<std::uint8_t>)> ResultCallback;

    static bool schedule(const std::vector<uint8_t> &data);
    static void bind(COMMANDS cmd, Func&& callback, ResultCallback&& result_cb);
private:
    static std::map< std::uint32_t, std::list< std::pair<Func, ResultCallback> > > _callbacks_map;
};

#endif /* SCHEDULER_H */
