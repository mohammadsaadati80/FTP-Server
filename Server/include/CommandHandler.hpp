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
#include <cstdio>
#include <cstring>
#include <sys/un.h>
#include <sys/stat.h>


#include "UserManager.hpp"

#define MAX_BUFFER_SIZE 1024
#define DATA_NOTHING " "

class CommandHandler
{
public :
    std::vector<std::string> get_command(char buf[MAX_BUFFER_SIZE] , int fd);
    const std::string current_date_time();
    void write_log(std::string filetext);
    double get_file_size(std::string filename);
    std::string exec(const char* cmd);
    bool is_exist(std::string name);

    static inline std::vector<std::string> files;   
};

#endif