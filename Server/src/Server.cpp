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
        cout << "Failed to create a socket." << endl;
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(int)) < 0)
    {
        cout << "Failed to set socket option." << endl;
        exit(EXIT_FAILURE);
    }

    if (bind(server_socket_fd, (struct sockaddr*)& server_sin, sizeof(server_sin)) < 0)
    {
        cout << "Failed to bind a socket." << endl;
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket_fd, MAX_CONNECTIONS) < 0)
    {
        cout << "Failed to listen." << endl;
        exit(EXIT_FAILURE);
    }

    return server_socket_fd;
}

void Server::run_server()
{
    CommandHandler command_handler;
    int command_channel_fd = run_socket(command_channel_port);
    int data_channel_fd = run_socket(data_channel_port);
    int max_fd = command_channel_fd;
    int activity;
    char buffer[MAX_BUFFER_SIZE] = {0};
    fd_set read_fds, copy_fds;
    FD_ZERO(&copy_fds);
    FD_SET(command_channel_fd, &copy_fds);
    cout << "Server is running ..." << endl;

    while (true) {
        memcpy(&read_fds, &copy_fds, sizeof(copy_fds)); 
        activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL); 
        if (activity < 0)
        {
            cout << "Failed to select." << endl;
            return;
        }
        for (int fd = 0; activity > 0 && fd <= max_fd; fd++) 
        {
            if (FD_ISSET(fd, &read_fds)) 
            {
                if (fd == command_channel_fd)  // New connection.
                { 
                    int new_command_channel_socket, new_data_channel_socket;
                    if ((new_command_channel_socket = accept(command_channel_fd, NULL, NULL)) < 0)
                    {
                        cout << endl << "Failed to accept new command channel socket." << endl;
                        return;
                    }
                    if ((new_data_channel_socket = accept(data_channel_fd, NULL, NULL)) < 0)
                    {
                        cout << endl << "Failed to accept new data channel socket." << endl;
                        return;
                    }
                    UserManager::add_connected_user(new_command_channel_socket, new_data_channel_socket);
                    cout << endl << "New connection accepted with command channel fd = " << new_command_channel_socket 
                        << " and data channel fd = " << new_data_channel_socket << "." << endl;
                    FD_SET(new_command_channel_socket, &copy_fds);
                    if (new_command_channel_socket > max_fd)
                        max_fd = new_command_channel_socket;
                }
                else  // New readable socket.
                { 
                    bool close_connection = false;
                    memset(buffer, 0, sizeof buffer);
                    int recive_result = recv(fd, buffer, sizeof(buffer), 0);
                    if (recive_result == 0 || (recive_result < 0 && errno != EWOULDBLOCK))
                        close_connection = true;
                    if (recive_result > 0) // Data is received.
                    { 
                        cout << endl << "Message from client with fd = " << fd << " :  " << buffer << endl;
                        vector<string> recive_result = command_handler.get_command(buffer , fd);
                        send(fd , recive_result[COMMAND_CHANNEL_RESPONE].c_str() , recive_result[COMMAND_CHANNEL_RESPONE].size() , 0);
                        send(UserManager::get_connected_user_by_fd(fd)->get_data_socket() , recive_result[DATA_CHANNEL_RESPONE].c_str() , recive_result[DATA_CHANNEL_RESPONE].size() , 0);
                    }
                    if (close_connection) 
                    {
                        close(fd);
                        int data_fd = UserManager::get_connected_user_by_fd(fd)->get_data_socket();
                        close(data_fd);
                        UserManager::remove_connected_user(fd);
                        cout << endl << "Client with command channel fd = " << fd 
                            << " and data channel fd = " << data_fd << " successfully closed." << endl;
                        FD_CLR(fd, &copy_fds);
                        if (fd == max_fd)
                            while (FD_ISSET(max_fd, &copy_fds) == 0)
                                max_fd -= 1;
                    }
                }
            }
        }
    }
}