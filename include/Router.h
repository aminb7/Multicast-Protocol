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
    Router(std::string listen_port, std::string server_ip);
    ~Router() = default;

    void start();
    void handle_command(std::string command);
    void close_others_fds(std::map<int, std::string> others_fds);
    void handle_connect_router(std::string router_port, std::string link);
    void handle_change_cost(std::string router_port, std::string cost);
    void handle_disconnect(std::string router_port);
    void handle_show();

    void show_unicast_table();
    void show_multicast_table();

    void handle_connection_message(std::string pipe_message);

    void accept_router_connect(std::string pipe_name, std::string link_name);
    void accept_client_connect(std::string client_ip);
    void accept_groupserver_connect(std::string groupserver_ip);

    void make_router_router_pipes(std::string router_port);

    void handle_router_message(std::string router_message, std::string sender_router_port);
    void handle_server_message(std::string server_message);
    std::map<int, std::string> add_routers_to_set(fd_set& fds, int& max_fd);
    void accept_router_change_cost(std::string router_port, std::string cost);
    void accept_router_disconnect(std::string router_port);

    void handle_client_message(std::string client_message);
    std::map<int, std::string> add_clients_to_set(fd_set& fds, int& max_fd);

    void handle_send(std::string message, std::string sender_router_port);

    void handle_groupserver_message(std::string groupserver_message);
    std::map<int, std::string> add_groupservers_to_set(fd_set& fds, int& max_fd);

    void handle_join_update(std::string client_ip, std::string group_ip);

    void handle_leave_update(std::string client_ip, std::string group_ip);

    std::pair<std::string, std::string> find_destination(std::string client_ip);

private:
    std::string listen_port;

    /// Map from link port to its link.
    std::map<std::string, Link*> links;

    std::pair<std::string, std::string> router_to_server_pipe;

    /// Map from client ip to its read and write pipes.
    std::map<std::string, std::pair<std::string, std::string>> clients_pipes;

    // Map from group ip to its read and write pipes.
    std::map<std::string, std::pair<std::string, std::string>> group_servers_pipes;

    std::map<std::string, std::vector<std::string>> multicast_table;

    std::vector<std::pair<std::string, std::string>> unicast_table;
};

