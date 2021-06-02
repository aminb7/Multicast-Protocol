#include <string>
#include <curses.h>
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

class Server
{
public:
    Server(std::string server_ip);
    ~Server() = default;

    void start();

private:
    std::string server_ip;
};
