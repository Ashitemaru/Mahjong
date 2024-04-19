#pragma once

#include "tcp_terminal.h"

class GameController {
    LimitedClientTCPServer *server;

public:
    GameController(unsigned short port);
    ~GameController();
    
    void start();
};