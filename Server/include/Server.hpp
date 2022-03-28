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
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "ConfigurationParser.hpp"
#include "UserManager.hpp"
#include "CommandHandler.hpp"

#define MAX_CONNECTIONS 10

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

#endif