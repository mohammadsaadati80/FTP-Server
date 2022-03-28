#include "Server.hpp"

using namespace std;

int Server::run_socket(int port)
{
    struct sockaddr_in server_sin;
    int server_socket_fd;
    server_sin.sin_port = htons(port);
    server_sin.sin_addr.s_addr = inet_addr("127.0.0.1");;
    server_sin.sin_family = AF_INET;
    int opt = 1;
    
    if ((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Failed to create a socket" << endl;
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(int)) < 0)
    {
        cout << "Failed to set socket option" << endl;
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

    return server_socket_fd;
}

void Server::run_server()
{
    CommandHandler ch1;
    int command_fd = run_socket(command_channel_port);
    int data_fd = run_socket(data_channel_port);

    fd_set read_fds, copy_fds;
    FD_ZERO(&copy_fds);
    FD_SET(command_fd, &copy_fds);
    int max_fd = command_fd;
    int activity;
    char buf[MAX_BUFFER_SIZE] = {0};
    printf("Server is starting ...\n");

    while (true) {
        memcpy(&read_fds, &copy_fds, sizeof(copy_fds)); 

        activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL); 

        if (activity < 0)
            return;

        int ready_sockets = activity;
        for (int fd = 0; fd <= max_fd  &&  ready_sockets > 0; ++fd) {
            if (FD_ISSET(fd, &read_fds)) { 
                if (fd == command_fd) { // New connection.
                    int new_command_socket;
                    if ((new_command_socket = accept(command_fd, NULL, NULL)) < 0)
                        return;
                    int new_data_socket;
                    if ((new_data_socket = accept(data_fd, NULL, NULL)) < 0)
                        return;
                    
                    UserManager::add_connected_user(new_command_socket, new_data_socket);
                    FD_SET(new_command_socket, &copy_fds);
                    if (new_command_socket > max_fd)
                        max_fd = new_command_socket;
                }
                else { // New readable socket.
                    bool close_connection = false;
                    memset(buf, 0, sizeof buf);
                    int result = recv(fd, buf, sizeof(buf), 0);

                    if (result < 0)
                        if (errno != EWOULDBLOCK)
                            close_connection = true;

                    if (result == 0) 
                        close_connection = 1;
                    
                    if (result > 0) { // Data is received.
                        vector<string> result = ch1.get_command(buf , fd);
                        send(fd , result[COMMAND].c_str() , result[COMMAND].size() , 0);
                        send(UserManager::get_user_by_fd(fd)->get_data_socket() , result[1].c_str() , result[1].size() , 0);
                    }

                    if (close_connection) {
                        close(fd);
                        close(UserManager::get_user_by_fd(fd)->get_data_socket());
                        UserManager::remove_connected_user(fd);
                        FD_CLR(fd, &copy_fds);
                        if (fd == max_fd)
                            while (FD_ISSET(max_fd, &copy_fds) == 0)
                                max_fd -= 1;
                    }
                }
            }
        }
        printf("---------------- Event ----------------\n");
    }
}