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
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/un.h>
#include <sys/stat.h>
#include "ConfigurationParser.hpp"
#include <experimental/filesystem>

#define MESSAGE_BUFFER_SIZE 2048
constexpr int CONFIG_FILE = 1;

class Client
{
public:
    void run_client();
    void write_downloaded_data_to_file(char buffer[MESSAGE_BUFFER_SIZE]);

    static inline int command_channel_port;
    static inline int data_channel_port;
    static inline int number_of_downloaded_file = 0;
};

#endif