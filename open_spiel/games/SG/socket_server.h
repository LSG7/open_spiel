#ifndef OPEN_SPIEL_GAMES_SG_SERVER_H_
#define OPEN_SPIEL_GAMES_SG_SERVER_H_

#include <thread>

class SocketServer {
public:
    SocketServer(int port);
    ~SocketServer();
    void start();
    void stop();
    void send();

private:
    void accept_connections();
    void handle_client(int client_socket);

    int server_fd;
    int port;
    bool running;
    std::thread accept_thread;
};

#endif