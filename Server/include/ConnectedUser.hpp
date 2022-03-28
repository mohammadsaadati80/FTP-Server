#ifndef __CONNECTED_USER_HPP__
#define __CONNECTED_USER_HPP__

#include <string>
#include <vector>
#include <iostream>

#include "User.hpp"

class ConnectedUser
{
public:  
    ConnectedUser(int command_socket, int data_socket);
    void set_user(User* _user);
    void set_is_username_entered(bool _state);
    void set_is_password_entered(bool _state);
    void set_current_directory(std::string path);
    User* get_user();
    int get_command_socket();
    int get_data_socket();
    bool get_is_username_entered();
    bool get_is_passsword_entered();
    std::string get_current_directory();

private:   
    User* user;
    int command_channel_socket_fd;
    int data_channel_socket_fd;
    bool is_username_entered;
    bool is_passsword_entered;
    std::string current_directory;    
};

#endif