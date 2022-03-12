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
    static User* find_user(std::string user_name);
    static std::vector<User*> users;
};

#endif