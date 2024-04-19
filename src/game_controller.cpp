#include <cstring>
#include <sys/socket.h>

#include "game_controller.h"

GameController *GameController::instance = nullptr;

GameController::GameController() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
}

GameController *GameController::getInstance() {
    if (instance == nullptr) instance = new GameController();
    return instance;
}

GameController::~GameController() {

}