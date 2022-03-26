#include "UserManager.hpp"

using namespace std;

vector<User*> UserManager::users;
vector<ConnectedUser*> UserManager::connected_users;

User* UserManager::find_user_by_username(std::string username)
{
    for(User* user : UserManager::users)
    {
        if(user->get_username() == username)
            return user;
    }
    return nullptr;
}

User* UserManager::find_user_by_index(int index)
{
    int user_size = users.size();
    if (index < user_size)
        return users[index];
    return nullptr;
}

std::vector <User*> UserManager::get_all_users()
{
    return users;
}

User* UserManager::find_user_by_fd(int fd)
{
    for(User* user : UserManager::users)
    {
        if(user->get_fd() == fd)
            return user;
    }
    return nullptr;
}

void UserManager::add_connected_user(int command_socket, int data_socket) 
{
    UserManager::connected_users.push_back(new ConnectedUser(command_socket, data_socket));
}

void UserManager::remove_connected_user(int socket) 
{
    for(size_t i = 0; i < connected_users.size(); i++) {
        if (UserManager::connected_users[i]->get_command_socket() == socket) {
            UserManager::connected_users.erase(UserManager::connected_users.begin() + i);
            break;
        }
    }
}

ConnectedUser* UserManager::get_user_by_fd(int fd)
{
    for(size_t i = 0; i < connected_users.size(); ++i)
        if (connected_users[i]->get_command_socket() == fd)
            return connected_users[i];
    return nullptr;
}