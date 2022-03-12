#ifndef __CLIENT_HPP__
#define __LIENT_HPP__

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024

class Client
{
public:
    void run_client();
};

#endif