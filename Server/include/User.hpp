#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>

class User
{
public:
    User( const std::string& username, const std::string& password, const bool& is_admin, double available_size);
    std::string get_username();
    std::string get_password();
    bool is_admin_user();
    double get_available_size();
    void decrease_available_size(double file_size);

private:
    std::string username;
    std::string password;
    bool is_admin;
    double available_size;

};

#endif