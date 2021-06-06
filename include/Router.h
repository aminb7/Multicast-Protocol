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
#include "../include/Link.h"

class Router
{
public:
    Router(std::string listen_port);
    ~Router() = default;

    void start();
    void handle_command(std::string command);
    void close_others_fds(std::map<int, std::string> others_fds);
    void handle_connect_router(std::string router_port, std::string link);
    void handle_change_cost(std::string link_name, std::string cost);
    void handle_disconnect(std::string link_name);
    void handle_show();

    void handle_pip_message(std::string pipe_message);
    void handle_router_message(std::string router_message);

    void make_router_router_pipes(std::string router_port);
    void accept_router_connect(std::string pipe_name, std::string link_name);
    std::map<int, std::string> add_routers_to_set(fd_set& fds, int& max_fd);
    void accept_router_change_cost(std::string link_name, std::string cost);
    void accept_router_disconnect(std::string link_name);

private:
    std::string listen_port;

    /// Map from link name to its link.
    std::map<std::string, Link*> links;
};

