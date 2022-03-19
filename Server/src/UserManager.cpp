#include "UserManager.hpp"

using namespace std;

std::vector<User*> UserManager::users;

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
    cout << user_size << endl;
    if (index < user_size)
        return users[index];
    return nullptr;
}