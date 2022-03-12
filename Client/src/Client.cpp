#include "Client.hpp"

using namespace std;

void Client::run_client()
{
    int client_socket_fd, client_data_socket_fd;
    if ((client_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Failed to create a socket." << endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_command_address;
    server_command_address.sin_family = AF_INET;
    server_command_address.sin_port = htons(COMMAND_CHANNEL_PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_command_address.sin_addr) <= 0) {
        cout << "The address is invalid or unsupported." << endl;
        exit(EXIT_FAILURE);
	}
	cout<<"command channel oppened!"<<endl;

    if (connect(client_socket_fd,(struct sockaddr*)&server_command_address, sizeof(server_command_address)) < 0)
    {
        cout << "Failed to establish a connection with the server." << endl;
        exit(EXIT_FAILURE);
    }
    cout<<"connected to server!"<<endl;

    if ((client_data_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "Failed to create a data socket." << endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_data_address;
    server_data_address.sin_family = AF_INET;
    server_data_address.sin_port = htons(DATA_CHANNEL_PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_data_address.sin_addr) <= 0) {
        cout << "The address is invalid or unsupported." << endl;
        exit(EXIT_FAILURE);
    }
    cout<<"data channel oppened!"<<endl;
    
    if (connect(client_data_socket_fd,(struct sockaddr*)&server_data_address, sizeof(server_data_address)) < 0)
    {
        cout << "Failed to establish a connection with the data server." << endl;
        exit(EXIT_FAILURE);
    }
    cout<<"connected to data server!"<<endl;

    thread new_thread(&Client::recive_file, this, (void*)&client_data_socket_fd);

    string command;
    char buffer[MESSAGE_BUFFER_SIZE];
    while(getline(cin, command))
    {
        strcpy(buffer, command.c_str());
        send(client_socket_fd, buffer, sizeof(buffer), 0);
        recv(client_socket_fd, buffer, sizeof(buffer), 0);
        cout << buffer << endl;
    }

    close(client_socket_fd);
}

void* Client::recive_file(void* _client_data_fd)
{
    char data_buffer[MESSAGE_BUFFER_SIZE] = {0};
    int client_data_socket_fd = *(int*) _client_data_fd;
    if (recv(client_data_socket_fd, data_buffer, MESSAGE_BUFFER_SIZE, 0) <= 0)
    {
        cout << "recive() failed." << endl;
        exit(EXIT_FAILURE);
    }
    int size = 0;
    FILE *file = fopen("downloaded_file.txt", "wb");
    for (int i = 0; i < MESSAGE_BUFFER_SIZE; i++)
    {
        if (data_buffer[i] == 0) break; 
        else size++;  
    }
    fwrite(data_buffer, size, 1, file);
    fclose(file);

    return NULL;
}