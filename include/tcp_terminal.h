#pragma once

#include <vector>
#include <arpa/inet.h>

class TCPClient {
    int client_fd;

public:
    TCPClient();
    ~TCPClient();

    void connect(const char *ip, unsigned short port);
    int send(const char *buffer, int size);
    int receive(char *buffer);
};

class LimitedClientTCPServer {
    int server_fd;
    int max_client_count;
    int *client_fd_list;

public:
    LimitedClientTCPServer(int max_client_count);
    ~LimitedClientTCPServer();

    void wait_all_connections(unsigned short port);
    int send(int id, const char *buffer, int size);
    int receive(int id, char *buffer);
};