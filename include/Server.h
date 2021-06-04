#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h> 
#include <dirent.h>
#include <fcntl.h> 
#include <map>
#include <utility>

#include "../include/Utilities.h"

class Server
{
public:
    Server(std::string server_ip);
    ~Server() = default;

    void start();
    void handle_command(std::string command);
    void handle_network_message(std::string pipe_message);

    void handle_client_connect(std::string name);
    void handle_group_server_connect(std::string name);

private:
    std::string server_ip;
    int server_port;
    std::pair<std::string, std::string> server_pipe;

    std::map<std::string, std::pair<std::string, std::string>> clients_pipes;
    std::map<std::string, std::pair<std::string, std::string>> group_servers_pipes;
};
