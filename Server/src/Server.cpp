#include "Server.hpp"

using namespace std;

vector <Connected_User> connected_users;
int users_size , connected_users_size;

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

void Command_handler::get_command(char buf[MAX_BUFFER_SIZE] , vector <User> users)
{
    if (buf[0] == 'u' && buf[1] == 's' && buf[2] == 'e' && buf[3] == 'r')
    {
        string uname = "";
        int cnt = 4;
        while (cnt < MAX_BUFFER_SIZE)
        {
            if (buf[cnt]!= ' ')
                uname += buf[cnt];
            cnt++;
        }
        int correctuser = 0 ;
        for (int i = 0 ; i < users_size ; i++)
        {
            if (users[i].get_username() == uname)
            {
                correctuser = 1;
                Connected_User tmp;
                tmp.username = uname;
                tmp.login = 0;
                cout << "331: User name okay,need password." << endl;
                connected_users.push_back(tmp);
            }
        }
        if (correctuser == 0)
            cout << "430: Invalid username or password" << endl;
    }
    else if (buf[0] == 'p' && buf[1] == 'a' && buf[2] == 's' && buf[3] == 's')
    {
        string pass = "";
        int cnt = 4;
        while (cnt < MAX_BUFFER_SIZE)
        {
            if (buf[cnt]!= ' ')
                pass += buf[cnt];
            cnt++;
        }
        int correctpass = 0;
        for (int i = 0 ; i < users_size ; i++)
        {
            if (users[i].get_password() == pass )
            {
                correctpass = 1;
                string uname = users[i].get_username();
                int was_in = 0;
                for (int j = 0 ; j < connected_users_size ; j++)
                {
                    if (connected_users[j].username == uname )
                    {
                        was_in = 1;
                        if (connected_users[j].login == 0)
                        {
                            connected_users[j].login = 1;
                            cout << "User logged in, proceed. Logged out if appropriate." << endl;
                        }
                        else
                        {
                            cout << "Already logged in." << endl;
                        }
                    }
                }
                if (was_in ==0)
                    cout << "503: Bad sequence of commands." << endl;
            }
        }
        if (correctpass == 0)
            cout << "430: Invalid username or password" << endl;
    }
}