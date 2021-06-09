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
    std::map<int, std::string> add_clients_to_set(fd_set& fds, int& max_fd);
    std::map<int, std::string> add_groupservers_to_set(fd_set& fds, int& max_fd);

    void close_clients_fds(std::map<int, std::string> clients_fds);
    void close_groupservers_fds(std::map<int, std::string> groupservers_fds);

    void handle_command(std::string command);
    void handle_connect_router(std::string router_port);

    void handle_connection_message(std::string message);
    void handle_client_connect(std::string name, std::string ip);
    void handle_group_server_connect(std::string name, std::string ip);
    void handle_router_connect(std::string port);

    void handle_client_message(std::string message, std::string client_name);
    void handle_get_group_list(std::string client_name);
    void handle_join_group(std::string client_name, std::string group_name);
    void handle_leave_group(std::string client_name, std::string group_name);

    void handle_groupservers_message(std::string message);

private:
    std::string server_ip;
    int server_port;
    std::pair<std::string, std::string> server_pipe;

    /// Map from client name to its read and write pipes.
    std::map<std::string, std::pair<std::string, std::string>> clients_pipes;

    /// Map from client name to its ip.
    std::map<std::string, std::string> clients_ips;

    /// Map from client name to its groups.
    std::map<std::string, std::vector<std::string>> clients_groups;

    /// Map from group name to its read and write pipes.
    std::map<std::string, std::pair<std::string, std::string>> group_servers_pipes;

    /// Map from router port to its read and write pipes.
    std::map<std::string, std::pair<std::string, std::string>> routers_pipes;

    /// Map from group name to its ip.
    std::map<std::string, std::string> groups_ip;
};
