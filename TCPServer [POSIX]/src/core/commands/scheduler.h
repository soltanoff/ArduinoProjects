#ifndef SHCEDULER_H
#define SHCEDULER_H
/* ================================================================================================================== */
#include <regex>
#include "command.h"
/* ================================================================================================================== */
extern std::vector<std::shared_ptr<CCommand>> COMMAND_LIST;

std::string command_scheduler(const std::string command);
#endif /* SHCEDULER_H */
