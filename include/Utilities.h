#include <string>
#include <iostream>
#include <algorithm>
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

#define DEFALAUT_IP "127.0.0.1"

#define STDIN 0

#define MAX_MESSAGE_SIZE 128
#define MAX_COMMAND_SIZE 128

#define ARG0 0
#define ARG1 1
#define ARG2 2
#define ARG3 3

//Message prefixes
#define ROUTER_MESSAGE_PREFIX "router"
#define CLIENT_MESSAGE_PREFIX "client"

/// Pipe defines
#define NETWORK_PIPE_NAME "network_pipe"
#define PIPE_ROOT_PATH "build/"
#define READ_PIPE "_r"
#define WRITE_PIPE "_w"
#define SERVER_PIPE "_s"
#define CLIENT_PIPE "_c"
#define GROUPSERVER_PIPE "_gs"
#define ROUTER_PIPE "_r"
#define READ_WRITE 0666

#define COMMAND_DELIMITER ' '
#define PIPE_NAME_DELIMITER '_'
#define MESSAGE_DELIMITER '%'

// Server
////  Commands
#define SERVER_TO_ROUTER_CONNECT_CMD "ConnectRouter"

// Client
////  Commands
#define SET_CLIENT_IP_CMD "SetIp"
#define GET_GROUP_LIST_CMD "GetGroupList"
#define JOIN_GROUP_CMD "JoinGroupList"
#define LEAVE_GROUP_CMD "LeaveGroupList"
#define SELECT_GROUP_CMD "SelectGroupList"
#define SEND_FILE_CMD "SendFile"
#define SEND_MESSAGE_CMD "SendMessage"
#define SHOW_GROUPS_CMD "ShowGroups"
#define SYNC_CMD "Sync"
#define SIGN_OUT_CMD "SignOut"
////  Messages
#define CLIENT_TO_SERVER_CONNECT_MSG "ClientServerConnect"
#define GET_GROUP_LIST_MSG "GetGroupList"

// GroupServer
//// Commands
#define SET_GROUP_IP_CMD "SetGroupIp"
#define SET_GROUPSERVER_IP_CMD "SetIp"
#define GROUPSERVER_TO_ROUTER_CONNECT_CMD "ConnectRouter"
#define GROUPSERVER_TO_SERVER_CONNECT_CMD "AddServer"
//// Messages
#define GROUPSERVER_TO_SERVER_CONNECT_MSG "GroupServerServerConnect"

// Router Commands
#define ROUTER_TO_ROUTER_CONNECT_CMD "ConnectRouter"
#define CHANGE_COST_CMD "ChangeCost"
#define DISCONNECT_LINK_CMD "Disconnect"
#define SHOW_CMD "Show"
//// Messages


int create_socket(std::string ip, int port);

std::vector<std::string> split(const std::string& s, char delimiter);
