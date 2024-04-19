#pragma once

#include <string>

#define INFO 0
#define ERROR 1

class Logger {
public:
    static void log(const std::string &message, int level);
    static void log(const char *message, int level);
};