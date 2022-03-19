#include "Server.hpp"

using namespace std;

vector <Connected_User> connected_users;
int users_size , connected_users_size;

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
    Command_handler ch1;
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
                    
                    // command_handler->get_user_manager()->add_user(new_command_socket, new_data_socket);
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
                        //vector<string> output = command_handler->get_command(buf, users, fd);
                        // send(fd , output[COMMAND].c_str() , output[COMMAND].size() , 0);
                        // send(command_handler->get_user_manager()->get_user_by_socket(fd)->get_data_socket(),
                        //         output[CHANNEL].c_str() , output[CHANNEL].size() , 0);
                        ch1.get_command(buf , fd);
                        cout << buf << endl;
                    }

                    if (close_connection) {
                        close(fd);
                        // close(command_handler->get_user_manager()->get_user_by_socket(fd)->get_data_socket());
                        // command_handler->get_user_manager()->remove_user(fd);
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


string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


void Command_handler::get_command(char buf[MAX_BUFFER_SIZE] , int fd)
{
    //UserManager *users1;
    vector <User*> users = UserManager::get_all_users();
    //cout << buf << endl;
    //cout << users.size() << endl;
    //cout << fd << endl;
    //cout << users[0]->get_username() << endl;
    if (buf[0] == 'u' && buf[1] == 's' && buf[2] == 'e' && buf[3] == 'r')
    {
        string uname = "";
        int cnt = 5;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                uname += buf[cnt];
            cnt++;
        }
        //cout << "uname is " << uname << endl;
        int correctuser = 0 ;
        for (int i = 0 ; i < int(users.size()) ; i++)
        {
            if (users[i]->get_username() == uname)
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
        int cnt = 5;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                pass += buf[cnt];
            cnt++;
        }
        int correctpass = 0;
        for (int i = 0 ; i < int(users.size()) ; i++)
        {
            if (users[i]->get_password() == pass )
            {
                correctpass = 1;
                string uname = users[i]->get_username();
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
    else if (buf[0] == 'p' && buf[1] == 'w' && buf[2] == 'd')
    {
        string directory = exec("pwd");
        cout << "257: " << directory << endl;
    }
    else if (buf[0] == 'm' && buf[1] == 'k' && buf[2] == 'd')
    {
        string path = "";
        int cnt = 4;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                path += buf[cnt];
            cnt++;
        }
        string cmd = "mkdir " + path;
        string directory = exec(cmd.c_str());
        cout << "257: " << path << "created." << endl;
    }
    else if (buf[0] == 'd' && buf[1] == 'e' && buf[2] == 'l' && buf[3]=='e')
    {
        int cnt = 8;
        string name;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                name += buf[cnt];
            cnt++;
        }
        if (buf[5]=='-' && buf[6]=='f')
        {
            string cmd="rm " + name;
            string directory = exec(cmd.c_str());
            cout << "250: " << name << " deleted." << endl;
        }
        else if (buf[5]=='-' && buf[6]=='d')
        {
            string cmd="rm -r " + name;
            string directory = exec(cmd.c_str());
            cout << "250: " << name << " deleted." << endl;
        }
        else
            cout << "500: Error" << endl;
    }
    else if (buf[0] == 'l' && buf[1] == 's')          // badan send ro dar run server bbrim ---- dar yek khat ham bashad
    {
        string result = exec("ls");
        char result_arr [result.length() + 1];
        strcpy(result_arr, result.c_str());
        send(fd , result_arr , result.length() + 1, 0);
        cout << "226: List transfer done." << endl;
    }
    else if (buf[0] == 'c' && buf[1] == 'w' && buf[2] == 'd')       // check shavad
    {
        int cnt = 4;
        string directory;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                directory += buf[cnt];
            cnt++;
        }
        string cmd = "cd " + directory ;
        string result = exec(cmd.c_str());
        cout << "250: Successful change." << endl;
    }
    else if (buf[0] == 'r' && buf[1] == 'e' && buf[2] == 'n' && buf[3] == 'a' && buf[4] == 'm' && buf[5] == 'e') 
    {
        int cnt = 7;
        string from , to;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                from += buf[cnt];
            cnt++;
        }
        cnt ++;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                to += buf[cnt];
            cnt++;
        }
        string cmd = "mv " + from + " " + to ;
        string result = exec(cmd.c_str());
        cout << "250: Successful change." << endl;
    }
}










