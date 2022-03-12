#include "User.hpp"

using namespace std;

User::User(const string& username, const string& password, const bool& is_admin, double available_size)
        : username(username)
        , password(password)
        , is_admin(is_admin)
        , available_size(available_size)
{
}

std::string User::get_username()
{
        return username;
}

std::string User::get_password()
{
        return password;
}

bool User::is_admin_user()
{
        return is_admin;
}

double User::get_available_size() {
    return available_size;
}

bool User::is_matched_with(string _username, string _password) {
    if (username == _username && password == _password)
        return true;
    return false;
}

void User::decrease_available_size(double file_size) {
   available_size -= (file_size/1000);
}