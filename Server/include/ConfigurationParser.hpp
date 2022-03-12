#ifndef __CONFIGURATION_PARSER_HPP__
#define __CONFIGURATION_PARSER_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "User.hpp"
#include "json.hpp"

using json = nlohmann::json;

class ConfigurationParser
{
public:
    ConfigurationParser(const std::string& config_file_path);
    std::vector<User*> get_users();
    std::vector<std::string> get_files();
    
private:
    void parse();

    std::string config_file_path;
    std::vector<User*> users;
    std::vector<std::string> files;
};

#endif