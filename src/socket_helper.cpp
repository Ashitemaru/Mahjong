#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <format>

#include "socket_helper.h"
#include "logger.h"

int SocketHelper::create_socket() {
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd == -1) {
        Logger::log("Failed to create socket.", ERROR);
        return -1;
    }

    Logger::log(std::format("Succeeded in creating socket, fd set to {}.", fd), INFO);
    return fd;
}

int SocketHelper::bind_socket(int fd, unsigned short port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        Logger::log("Failed to bind socket.", ERROR);
        return -1;
    }

    Logger::log(std::format("Succeeded in binding socket to port {}.", port), INFO);
    return 0;
}

int SocketHelper::listen_socket(int fd) {
    if (listen(fd, 128) == -1) {
        Logger::log("Failed to listen on socket.", ERROR);
        return -1;
    }

    Logger::log("Succeeded in listening on socket.", INFO);
    return 0;
}

int SocketHelper::close_socket(int fd) {
    if (close(fd) == -1) {
        Logger::log("Failed to close socket.", ERROR);
        return -1;
    }

    Logger::log("Succeeded in closing socket.", INFO);
    return 0;
}

int SocketHelper::connect_server(int fd, const char *ip, unsigned short port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr.s_addr);

    if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        Logger::log(std::format("Failed to connect to server {}:{}.", ip, port), ERROR);
        return -1;
    }

    Logger::log(std::format("Succeeded in connecting to server {}:{}.", ip, port), INFO);
    return 0;
}

int SocketHelper::accept_client(int fd) {
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    int client_fd = accept(fd, (struct sockaddr *) &addr, &addr_len);
    if (client_fd == -1) {
        Logger::log("Failed to accept connection.", ERROR);
        return -1;
    }

    Logger::log(std::format("Succeeded in accepting connection with fd {}.", client_fd), INFO);
    return client_fd;
}

int SocketHelper::receive_lengthed_data(int fd, char *buffer, int size) {
    int recieve_size = 0;
    int remaining = size;
    char *ptr = buffer;
    while (remaining > 0) {
        recieve_size = read(fd, ptr, remaining);
        if (recieve_size == -1) {
            Logger::log(std::format("Failed to receive data from socket {}.", fd), ERROR);
            return -1;
        } else if (recieve_size > 0) {
            ptr += recieve_size;
            remaining -= recieve_size;
        }
    }

    return size;
}

int SocketHelper::send_lengthed_data(int fd, const char *buffer, int size) {
    int send_size = 0;
    int remaining = size;
    const char *ptr = buffer;
    while (remaining > 0) {
        send_size = write(fd, ptr, remaining);
        if (send_size == -1) {
            Logger::log(std::format("Failed to send data to socket {}.", fd), ERROR);
            return -1;
        } else if (send_size > 0) {
            ptr += send_size;
            remaining -= send_size;
        }
    }

    return size;
}

int SocketHelper::receive_data(int fd, char *buffer) {
    if (fd <= 0 || buffer == nullptr) {
        Logger::log("Invalid arguments to receive_data.", ERROR);
        return -1;
    }

    int message_length = 0;
    int return_code = receive_lengthed_data(fd, (char *) &message_length, sizeof(int));
    message_length = ntohl(message_length);

    return_code = receive_lengthed_data(fd, buffer, message_length);
    if (return_code != message_length) {
        /**
         * The first step failed: message_length = 0 and return_code = -1
         * The second step failed: message_length = N and return_code = -1
         * The second step succeeded but unfull data: message_length = N and return_code = M < N
         */
        Logger::log(std::format("Failed to receive data from socket {}.", fd), ERROR);
        return -1;
    }

    return message_length;
}

int SocketHelper::send_data(int fd, const char *buffer, int size) {
    if (fd <= 0 || buffer == nullptr) {
        Logger::log("Invalid arguments to send_data.", ERROR);
        return -1;
    }

    int message_length = htonl(size);
    char *message = new char[size + sizeof(int)];
    memcpy(message, &message_length, sizeof(int));
    memcpy(message + sizeof(int), buffer, size);

    int return_code = send_lengthed_data(fd, message, size + sizeof(int));
    delete[] message;
    if (return_code == -1) {
        Logger::log(std::format("Failed to send data to socket {}.", fd), ERROR);
        return -1;
    }

    return size;
}