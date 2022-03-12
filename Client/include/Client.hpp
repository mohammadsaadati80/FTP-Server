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

#define MESSAGE_BUFFER_SIZE 1024
#define COMMAND_CHANNEL_PORT 5000
#define DATA_CHANNEL_PORT 5001

class Client
{
public:
    void run_client();
    void* recive_file(void* _client_data_fd);
};

#endif