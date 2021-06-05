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

class Router
{
public:
    Router(std::string listen_port);
    ~Router() = default;

    void start();
    void handle_command(std::string command);
    void handle_connect_router(std::string router_port, std::string link);
    void handle_change_cost(std::string link, std::string cost);
    void handle_disconnect(std::string link);
    void handle_show();

    void handle_pip_message(std::string pipe_message);

private:
    std::string listen_port;
};
