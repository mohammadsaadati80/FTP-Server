#include "Server.hpp"

using namespace std;

void Server::run_server()
{
    struct sockaddr_in server_sin;
    int server_socket_fd;
    server_sin.sin_port = htons(5000);
    server_sin.sin_addr.s_addr = inet_addr("127.0.0.1");;
    server_sin.sin_family = AF_INET;
    
    if ((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Failed to create a socket" << endl;
        exit(EXIT_FAILURE);
    }

    if (bind(server_socket_fd, (struct sockaddr*)& server_sin, sizeof(server_sin)) < 0)
    {
        cout << "Failed to bind a socket" << endl;
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket_fd, MAX_CONNECTIONS) < 0)
    {
        cout << "Failed to listen" << endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in client_sin;
    int client_in_len;
    int new_server_fd ;
    if ((new_server_fd = accept(server_socket_fd, (struct sockaddr*)& client_sin, (socklen_t*)&client_in_len)) < 0)
    {
        cout << "Failed to accept." << endl;
    }

    char buf[MAX_BUFFER_SIZE];
    while (true)
    {
        if ((client_in_len = recv(new_server_fd, buf, sizeof(buf), 0)))
            cout << buf << endl;
    }
    
    close(server_socket_fd);
    close(new_server_fd);
}