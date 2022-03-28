#include "ConnectedUser.hpp"

using namespace std;

ConnectedUser::ConnectedUser(int command_socket, int data_socket)
    : command_channel_socket_fd(command_socket)
    , data_channel_socket_fd(data_socket) 
{
    user = nullptr;
    is_username_entered = false;
    is_passsword_entered = false;
    current_directory = "";  

}

void ConnectedUser::set_user(User* _user) 
{
    user = _user;
}

void ConnectedUser::set_is_username_entered(bool _state)
{
    is_username_entered = _state;
}
void ConnectedUser::set_is_password_entered(bool _state)
{
    is_passsword_entered = _state;
}

void ConnectedUser::set_current_directory(string path) 
{
    current_directory = path;
}

User* ConnectedUser::get_user() 
{
    return user;
}

int ConnectedUser::get_command_socket() 
{
    return command_channel_socket_fd;
}

int ConnectedUser::get_data_socket() 
{
    return data_channel_socket_fd;
}

bool ConnectedUser::get_is_username_entered() 
{
    return is_username_entered;
}

bool ConnectedUser::get_is_passsword_entered()
{
    return is_passsword_entered;
}

string ConnectedUser::get_current_directory() 
{
    return current_directory;
}