#include "Client.hpp"

using namespace std;

void Client::run_client()
{
    int client_socket_fd;
    if ((client_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Failed to create a socket" << endl; 
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(5000);
    server_address.sin_family = AF_INET;

    if (connect(client_socket_fd,(struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        cout << "Failed to establish a connection with the server." << endl;
        exit(EXIT_FAILURE);
    }
    cout<<"connected to server!"<<endl;

    char buf[MAX_BUFFER_SIZE] = "yo yo XD";
    send(client_socket_fd, buf, sizeof(buf), 0);

}