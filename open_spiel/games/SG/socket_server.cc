#include <iostream>
#include <vector>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#include "socket_server.h"

SocketServer::SocketServer(int port) : port(port), running(false), server_fd(-1) {}

SocketServer::~SocketServer() {
    stop();
}

void SocketServer::start() {
    struct sockaddr_in address;
    int opt = 1;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    running = true;
    accept_thread = std::thread(&SocketServer::accept_connections, this);
    std::cout << "Server is running and accepting connections on port " << port << "...\n";
}

void SocketServer::stop() {
    running = false;
    if (accept_thread.joinable()) {
        accept_thread.join();
    }
    if (server_fd != -1) {
        close(server_fd);
    }
}

void SocketServer::accept_connections() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    while (running) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            if (running) {
                perror("accept");
            }
            continue;
        }
        std::cout << "Client connected\n";
        std::thread(&SocketServer::handle_client, this, new_socket).detach();
    }
}

#define BUF_SIZE 100
void SocketServer::handle_client(int client_socket)
{
    char buffer[BUF_SIZE] = {0,};
    while (1) {
        memset(buffer, 0, BUF_SIZE);
        int bytes_received = recv(client_socket, buffer, BUF_SIZE, 0);
        if (bytes_received > 0) {
            // 데이터가 수신된 경우
            // buffer에 있는 데이터를 처리하거나 필요에 따라 다른 동작을 수행
            std::cout << "Server recieved data\n";
        } else if (bytes_received == 0) {
            // 클라이언트가 연결을 종료한 경우
            // 적절한 처리를 수행
            std::cout << "Client disconnected\n";
            break;
        } else {
            // 오류 발생
            // 에러 처리 로직을 수행
        }
        
    }
}
/*
void SocketServer::send_obs_vector(int client_socket) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    send(client_socket, vec.data(), vec.size() * sizeof(int), 0);
    std::cout << "Data sent to client\n";
    close(client_socket);
}
*/

/*
int server_init() {
    SocketServer server(PORT);
    server.start();

    // 메인 스레드는 다른 작업을 계속 수행
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 예시로 1초마다 대기
    }

    server.stop();
    return 0;
}
*/