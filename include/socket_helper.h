#pragma once

class SocketHelper {
    static int receive_lengthed_data(int fd, char *buffer, int size);
    static int send_lengthed_data(int fd, const char *buffer, int size);
    
public:
    static int create_socket();
    static int bind_socket(int fd, unsigned short port);
    static int listen_socket(int fd);
    static int close_socket(int fd);

    static int connect_server(int fd, const char *ip, unsigned short port);
    static int accept_client(int fd);

    static int receive_data(int fd, char *buffer);
    static int send_data(int fd, const char *buffer, int size);
};