#ifndef __USER_MANAGER_HPP__
#define __USER_MANAGER_HPP__

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

#include "User.hpp"
#include "ConfigurationParser.hpp"
#include "ConnectedUser.hpp"

class UserManager
{
public:
    
    static User* find_user_by_username(std::string user_name);
    static ConnectedUser* get_user_by_fd(int socket);
    static void add_connected_user(int command_socket, int data_socket);
    static void remove_connected_user(int socket);
    
    static std::vector<User*> users;
    static std::vector<ConnectedUser*> connected_users;
};

#endif