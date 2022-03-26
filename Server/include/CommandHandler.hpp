#ifndef __COMMAND_HANDLER_HPP__
#define __COMMAND_HANDLER_HPP__

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

#include "UserManager.hpp"

#define MAX_BUFFER_SIZE 1024

class CommandHandler
{
public :
    std::vector<std::string> get_command(char buf[MAX_BUFFER_SIZE] , int fd);
    
};

#endif