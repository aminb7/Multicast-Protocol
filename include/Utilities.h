#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define LOCAL_IP "127.0.0.1"

#define NETWORK_PIPE_NAME "network_pipe"
#define PIPE_ROOT_PATH "build/"
#define READ_PIPE "_r"
#define WRITE_PIPE "_w"
#define SERVER_PIPE "_s"
#define CLIENT_PIPE "_c"
#define GROUPSERVER_PIPE "_gs"
#define READ_WRITE 0666

#define MAX_MESSAGE_SIZE 128
#define MAX_COMMAND_SIZE 128

#define STDIN 0

#define CLIENT_TO_SERVER_CONNECT_MESSAGE "ClientServerConnect"
#define GROUPSERVER_TO_SERVER_CONNECT_MESSAGE "GroupServerServerConnect"

#define COMMAND_DELIMITER '%'

#define ARG0 0
#define ARG1 1
#define ARG2 2
#define ARG3 3

int create_socket(std::string ip, int port);

std::vector<std::string> split(const std::string& s, char delimiter);
