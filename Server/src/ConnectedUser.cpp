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

string ConnectedUser::get_username() 
{
    return user->get_username();
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

void ConnectedUser::decrease_available_size(double file_size) 
{
   user->decrease_available_size(file_size);
}

bool ConnectedUser::is_able_to_download(double file_size) 
{
    if (user->get_available_size() >= file_size/1000)
        return true;
    return false;
}

bool ConnectedUser::is_admin_user() 
{
    return user->is_admin_user();
}