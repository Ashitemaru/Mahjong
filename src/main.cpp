#include <iostream>

#include "game_controller.h"
#include "socket_helper.h"

int main(int argc, char **argv) {
    int fd = SocketHelper::create_socket();
    return 0;
}