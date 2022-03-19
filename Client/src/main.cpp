#include "Client.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Client client = Client();
    Client::command_channel_port = ConfigurationParser(argv[CONFIG_FILE]).get_command_channel_port();
    Client::data_channel_port = ConfigurationParser(argv[CONFIG_FILE]).get_data_channel_port();
    client.run_client();
    return 0;
}