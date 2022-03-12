#include "Server.hpp"

int main(int argc, char const *argv[])
{
    Server server = Server();
    UserManager::users = ConfigurationParser(argv[CONFIG_FILE]).get_users();
    Server::files = ConfigurationParser(argv[CONFIG_FILE]).get_files();
    server.run_server();
    return 0;
}