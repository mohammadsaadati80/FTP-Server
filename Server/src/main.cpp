#include "Server.hpp"

int main(int argc, char const *argv[])
{
    Server server = Server();
    UserManager::users = ConfigurationParser(argv[CONFIG_FILE]).get_users();
    CommandHandler::files = ConfigurationParser(argv[CONFIG_FILE]).get_files();
    Server::command_channel_port = ConfigurationParser(argv[CONFIG_FILE]).get_command_channel_port();
    Server::data_channel_port = ConfigurationParser(argv[CONFIG_FILE]).get_data_channel_port();
    server.run_server();
    return 0;
}