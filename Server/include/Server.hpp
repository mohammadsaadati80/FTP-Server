#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_CONNECTIONS 10
#define MAX_BUFFER_SIZE 1024

class Server
{
public:
    void run_server();
};

#endif