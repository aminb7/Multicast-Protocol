#include <string>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include "../include/Utilities.h"

class Server
{
public:
    Server(std::string server_ip);
    ~Server() = default;

    void start();
    void handle_command(std::string command);
    void handle_pip_message(std::string pipe_message);

private:
    std::string server_ip;
    int server_port;
};
