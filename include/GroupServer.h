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

class GroupServer
{
public:
    GroupServer(std::string group_name, std::string server_ip);
    ~GroupServer() = default;

    void start();
    void handle_command(std::string command);
    void handle_pip_message(std::string pipe_message);

private:
    std::string group_name;
    std::string server_ip;
};
