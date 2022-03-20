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
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <ctype.h>
#include <fstream>
#include <sys/stat.h>

#include "User.hpp"
#include "ConfigurationParser.hpp"
#include "UserManager.hpp"

#define MAX_CONNECTIONS 10
#define MAX_BUFFER_SIZE 1024
#define COMMAND 0
#define CHANNEL 1
constexpr int CONFIG_FILE = 1;

class Server
{
public:
    void run_server();
    int run_socket(int port);
    static inline std::vector<std::string> files; 
    static inline int command_channel_port;
    static inline int data_channel_port;    
};

class Connected_User
{
public:   
    std::string username;
    bool login;
    int fd;
};

class Command_handler
{
public :
    void get_command(char buf[MAX_BUFFER_SIZE] , int fd);
};

#endif