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

class GroupServer
{
public:
    GroupServer(std::string group_name, std::string server_ip);
    ~GroupServer() = default;

    void start();
    std::map<int, std::string> add_routers_to_set(fd_set& fds, int& max_fd);
    void close_others_fds(std::map<int, std::string> others_fds);

    void handle_command(std::string command);

    void handle_set_group_ip(std::string group_ip);
    void handle_set_groupserver_ip(std::string groupserver_ip);
    void handle_connect_router(std::string router_port);
    void handle_connect_server();

    void handle_pip_message(std::string pipe_message);

private:
    std::string group_name;
    std::string ip;
    std::string group_ip;

    std::string server_ip;

    std::pair<std::string, std::string> groupserver_to_server_pipe;

    /// Map from router port to its read and write pipes.
    std::map<std::string, std::pair<std::string, std::string>> groupserver_to_routers_pipes;
};
