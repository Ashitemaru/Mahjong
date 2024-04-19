#include <iostream>
#include <ctime>

#include "logger.h"

void Logger::log(const std::string &message, int level = 0) {
    std::string prefix;
    switch (level) {
        case 0:
            prefix = "[INFO]";
            break;
        case 1:
            prefix = "[ERROR]";
            break;
        default:
            prefix = "[UNKNOWN]";
            break;
    }
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::cout << prefix
              << "[" << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << "] "
              << message
              << std::endl;
}

void Logger::log(const char *message, int level = 0) {
    log(std::string(message), level);
}