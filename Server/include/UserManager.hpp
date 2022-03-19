#ifndef __USER_MANAGER_HPP__
#define __USER_MANAGER_HPP__

#include <string>
#include <vector>
#include <iostream>

#include "User.hpp"
#include "ConfigurationParser.hpp"

class UserManager
{
public:
    static User* find_user_by_username(std::string user_name);
    static User* find_user_by_index(int index);
    static std::vector<User*> users;
};

#endif