#include <iostream>
#include <cstring>
#include <string>

#include "game_controller.h"
#include "socket_helper.h"

int main(int argc, char **argv) {
    if (strcmp(argv[1], "0") == 0) {
        GameController game_controller(8080);
        game_controller.start();

    } else {
        int client_fd = SocketHelper::create_socket();
        SocketHelper::connect_server(client_fd, "127.0.0.1", 8080);

        std::string buffer;
        while (true) {
            std::cin >> buffer;
            SocketHelper::send_data(client_fd, buffer.c_str(), buffer.size());

            int response;
            SocketHelper::receive_data(client_fd, (char *) &response);
            std::cout << "Response: " << response << std::endl;
        }

    }
    return 0;
}