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

#define LOCAL_IP "127.0.0.1"
#define NETWORK_PIPE_NAME "network_pipe"
#define PIPE_ROOT_PATH "build/"
#define READ_PIPE "_r"
#define WRITE_PIPE "_w"
#define READ_WRITE 0666
#define MAX_MESSAGE_SIZE 128
#define MAX_COMMAND_SIZE 128
#define STDIN 0

int create_socket(std::string ip, int port);
