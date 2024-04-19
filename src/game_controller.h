#pragma once

class GameController {
    // Singleton instance
    static GameController *instance;

    int server_socket;

public:
    GameController();
    GameController(const GameController &) = delete;
    GameController &operator=(const GameController &) = delete;
    static GameController *getInstance();

    ~GameController();
};