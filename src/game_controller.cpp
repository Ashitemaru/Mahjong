#include "game_controller.h"

GameController::GameController(unsigned short port) {
    server = new LimitedClientTCPServer(1);
    server->wait_all_connections(port);
}

GameController::~GameController() {
    delete server;
}

void GameController::start() {
    char buffer[1024];
    while (true) {
        int message_length = server->receive(0, buffer);
        if (message_length == -1) continue;

        server->send(0, (char *) &message_length, sizeof(int));
    }
}