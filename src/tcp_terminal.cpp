#include <cstring>
#include <format>

#include "tcp_terminal.h"
#include "socket_helper.h"
#include "logger.h"

TCPClient::TCPClient() {
    client_fd = SocketHelper::create_socket();
}

TCPClient::~TCPClient() {
    SocketHelper::close_socket(client_fd);
}

void TCPClient::connect(const char *ip, unsigned short port) {
    SocketHelper::connect_server(client_fd, ip, port);
}

int TCPClient::send(const char *buffer, int size) {
    return SocketHelper::send_data(client_fd, buffer, size);
}

int TCPClient::receive(char *buffer) {
    return SocketHelper::receive_data(client_fd, buffer);
}

LimitedClientTCPServer::LimitedClientTCPServer(int max_client_count):
    max_client_count(max_client_count) {
    server_fd = SocketHelper::create_socket();
    client_fd_list = new int[max_client_count];
    memset(client_fd_list, 0, max_client_count * sizeof(int));
}

LimitedClientTCPServer::~LimitedClientTCPServer() {
    SocketHelper::close_socket(server_fd);
    delete[] client_fd_list;
}

void LimitedClientTCPServer::wait_all_connections(unsigned short port) {
    SocketHelper::bind_socket(server_fd, port);
    SocketHelper::listen_socket(server_fd);

    int connected_client_num = 0;
    while (connected_client_num < max_client_count) {
        int client_fd = SocketHelper::accept_client(server_fd);
        if (client_fd == -1) continue;

        client_fd_list[connected_client_num] = client_fd;
        connected_client_num++;
    }

    Logger::log("All clients are connected.", INFO);
}

int LimitedClientTCPServer::send(int id, const char *buffer, int size) {
    return SocketHelper::send_data(client_fd_list[id], buffer, size);
}

int LimitedClientTCPServer::receive(int id, char *buffer) {
    return SocketHelper::receive_data(client_fd_list[id], buffer);
}