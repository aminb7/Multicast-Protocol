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

#include "../include/Utilities.h"

class Client
{
public:
    Client(std::string name, std::string server_ip, std::string router_ip,
            std::string router_port);
    ~Client() = default;

    void start();
    void handle_command(std::string command);
    void handle_pip_message(std::string pipe_message);
private:

    std::string client_ip;
    int client_port;

    std::string name;
    std::string server_ip;
    std::string router_ip;
    std::string router_port;

    std::pair<std::string, std::string> client_to_server_pipe;
};
