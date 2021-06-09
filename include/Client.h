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
    void handle_set_ip(std::string ip);
    void handle_get_group_list();
    void handle_join_group(std::string group_name);
    void handle_leave_group(std::string group_name);
    void handle_select_group(std::string group_name);
    void handle_send_file(std::string file_name, std::string group_name);
    void handle_send_message(std::string message, std::string group_name);
    void handle_show_groups();
    void handle_sync();
    void handle_sign_out();

    void handle_pip_message(std::string pipe_message);
private:

    std::string client_ip;
    int client_port;

    std::string name;
    std::string server_ip;
    std::string router_ip;
    std::string router_port;

    std::vector<std::string> groups;

    std::pair<std::string, std::string> client_to_server_pipe;
    std::pair<std::string, std::string> client_to_router_pipe;
};
