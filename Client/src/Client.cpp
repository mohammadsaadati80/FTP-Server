#include "Client.hpp"

using namespace std;

void Client::run_client()
{
    int client_command_socket_fd, client_data_socket_fd;

    if ((client_command_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Failed to create command socket." << endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_command_address;
    server_command_address.sin_family = AF_INET;
    server_command_address.sin_port = htons(command_channel_port);
    if (inet_pton(AF_INET, "127.0.0.1", &server_command_address.sin_addr) <= 0) {
        cout << "The address is invalid or unsupported." << endl;
        exit(EXIT_FAILURE);
	}
	cout<<"Command channel oppened!"<< endl;

    if (connect(client_command_socket_fd,(struct sockaddr*)&server_command_address, sizeof(server_command_address)) < 0)
    {
        cout << "Failed to establish a connection with the server." << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Connected to server!" << endl << endl;

    if ((client_data_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "Failed to create data socket." << endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_data_address;
    server_data_address.sin_family = AF_INET;
    server_data_address.sin_port = htons(data_channel_port);
    if (inet_pton(AF_INET, "127.0.0.1", &server_data_address.sin_addr) <= 0) {
        cout << "The address is invalid or unsupported." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Data channel oppened!" << endl;
    if (connect(client_data_socket_fd,(struct sockaddr*)&server_data_address, sizeof(server_data_address)) < 0)
    {
        cout << "Failed to establish a connection with the data server." << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Connected to server!" <<endl << endl;

    cout << "Client is running ..." << endl;
    
    string command;
    char buffer[MESSAGE_BUFFER_SIZE];
    cout << endl << "Enter command:" << endl << ">> ";
    while(getline(cin, command)) {
        strcpy(buffer, command.c_str());
        send(client_command_socket_fd, buffer, sizeof(buffer), 0);
        memset(buffer, 0, sizeof buffer);
        recv(client_command_socket_fd, buffer, sizeof(buffer), 0);
        cout << endl << "Command channel respone message: " << endl << buffer << endl;
        memset(buffer, 0, sizeof buffer);
        recv(client_data_socket_fd , buffer, MESSAGE_BUFFER_SIZE, 0);
        if (buffer[0] != ' ')
            cout << endl << "Data channel respone message: " << endl << endl << buffer << endl;
        cout << endl << "Enter command:" << endl << ">> ";
    }
}