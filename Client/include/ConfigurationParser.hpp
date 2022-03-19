#ifndef __CONFIGURATION_PARSER_HPP__
#define __CONFIGURATION_PARSER_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

class ConfigurationParser
{
public:
    ConfigurationParser(const std::string& config_file_path);
    std::vector<std::string> get_files();
    int get_command_channel_port();
    int get_data_channel_port();
    
private:
    void parse();
    int command_channel_port;
    int data_channel_port;
    std::string config_file_path;
    std::vector<std::string> files;
};

#endif