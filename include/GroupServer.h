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
    std::string ip;
    std::string group_ip;

    std::string server_ip;

    std::pair<std::string, std::string> groupserver_to_server_pipe;
};
