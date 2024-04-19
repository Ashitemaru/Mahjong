#include <sys/socket.h>

#include "socket_helper.h"
#include "logger.h"

int SocketHelper::create_socket() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        Logger::log("Failed to create socket", ERROR);
        exit(-1);
    }

    Logger::log("Creating socket succeeded", INFO);
    return fd;
}