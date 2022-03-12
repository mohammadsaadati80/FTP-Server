#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

#include "User.hpp"
#include "ConfigurationParser.hpp"

#define MAX_CONNECTIONS 10
#define MAX_BUFFER_SIZE 1024

class Server
{
public:
    void run_server();
};

class Connected_User
{
public:   
    std::string username;
    bool login;
};

class Command_handler
{
public :
    void get_command(char buf[MAX_BUFFER_SIZE] , std::vector <User> users);
};

#endif