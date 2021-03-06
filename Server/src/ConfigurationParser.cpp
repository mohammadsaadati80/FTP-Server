#include "ConfigurationParser.hpp"

using namespace std;

ConfigurationParser::ConfigurationParser(const string& config_file_path) : config_file_path(config_file_path)
{
    parse();
}

void ConfigurationParser::parse()
{
    json json;
    ifstream file(config_file_path);
    file >> json;
    command_channel_port = json["commandChannelPort"].get<int>();
    data_channel_port = json["dataChannelPort"].get<int>();
    for (auto& user: json["users"])
    {
        users.push_back(
            new User(
            user["user"].get<string>(),
            user["password"].get<string>(),
            user["admin"].get<string>() == "true",
            stoi(user["size"].get<string>()))
        );
    }
    for (auto& file: json["files"])
        files.push_back(file.get<string>());
}

vector<User*> ConfigurationParser::get_users()
{
    return users;
}
vector<string> ConfigurationParser::get_files()
{
    return files;
}

int ConfigurationParser::get_command_channel_port()
{
    return command_channel_port;
}

int ConfigurationParser::get_data_channel_port()
{
    return data_channel_port;
}