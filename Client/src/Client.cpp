#include "Client.hpp"

using namespace std;
namespace fs = std::experimental::filesystem;

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
    bool is_retr = false;
    cout << endl << "Enter command:" << endl << ">> ";
    while(getline(cin, command)) { 
        
        memset(buffer, 0, MESSAGE_BUFFER_SIZE);    
        strcpy(buffer, command.c_str());       // Read command line 
        is_retr = (buffer[0] == 'r' && buffer[2] == 't');
        send(client_command_socket_fd, buffer, command.size(), 0);    // Send request to server

        memset(buffer, 0, sizeof buffer);
        recv(client_data_socket_fd , buffer, sizeof(buffer), 0);     //  Recive data channel respone message from server
        if (buffer[0] != ' ')
        {
            cout << endl << "Data channel respone message: " << endl << endl << buffer << endl;
            if(is_retr)
                write_downloaded_data_to_file(buffer);
        }

        memset(buffer, 0, sizeof buffer);
        recv(client_command_socket_fd, buffer, sizeof(buffer), 0);      //  Recive coommand channel respone message from server
        cout << endl << "Command channel respone message: " << endl << buffer << endl;

        cout << endl << "Enter command:" << endl << ">> ";
    }
}

void Client::write_downloaded_data_to_file(char buffer[MESSAGE_BUFFER_SIZE])
{
    ++number_of_downloaded_file;
    while(fs::is_regular_file("downloaded_file_" + to_string(number_of_downloaded_file) + ".txt"))
        ++number_of_downloaded_file;
    fstream myFile;
    myFile.open ("downloaded_file_" + to_string(number_of_downloaded_file) + ".txt", ios::out);
    myFile << buffer;
    myFile.close();
    cout << endl << "Data successfully downloaded and stored in downloaded_file_" 
        << to_string(number_of_downloaded_file) << ".txt file." << endl;
}