#ifndef __CLIENT_HPP__
#define __LIENT_HPP__

#include <iostream>
#include <string>
#include <string.h>
#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "ConfigurationParser.hpp"

#define MESSAGE_BUFFER_SIZE 1024
constexpr int CONFIG_FILE = 1;

class Client
{
public:
    void run_client();
    void* recive_file(void* _client_data_fd);
    static inline int command_channel_port;
    static inline int data_channel_port;
};

#endif