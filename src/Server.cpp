#include "../include/Server.h"

using namespace std;

int main(int argc, char* argv[]) {
    Server server(argv[1]);
    server.start();
    return 0;
}

Server::Server(string server_ip)
: server_ip(server_ip)
, server_port(8080)
, server_pipe((PIPE_ROOT_PATH + string(server_ip) + READ_PIPE), (PIPE_ROOT_PATH + string(server_ip) + WRITE_PIPE)) {
    // Create pipes for incoming connections.
    unlink(server_pipe.first.c_str());
	mkfifo(server_pipe.first.c_str(), READ_WRITE);
    unlink(server_pipe.second.c_str());
	mkfifo(server_pipe.second.c_str(), READ_WRITE);
}

void Server::start() {
    fd_set read_fds, copy_fds;
    FD_ZERO(&copy_fds);
    FD_SET(STDIN, &copy_fds);
    int max_fd = STDIN;
    int activity;
    char received_buffer[MAX_MESSAGE_SIZE] = {0};
    int server_pipe_fd = open(server_pipe.first.c_str(), O_RDWR);
    printf("Server is starting ...\n");
    while (true) {
        max_fd = server_pipe_fd;
        map<int, string> clients_fds = add_clients_to_set(copy_fds, max_fd);
        map<int, string> groupservers_fds = add_groupservers_to_set(copy_fds, max_fd);

        FD_SET(server_pipe_fd, &copy_fds);

        // Add fds to set
        memcpy(&read_fds, &copy_fds, sizeof(copy_fds));

        // Select
        cout << "> ";
        fflush(STDIN);
        activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (activity < 0)
            return;

        int ready_sockets = activity;
        for (int fd = 0; fd <= max_fd  &&  ready_sockets > 0; ++fd) {
            if (FD_ISSET(fd, &read_fds)) {
                memset(received_buffer, 0, sizeof received_buffer);

                // Receive command from command line.
                if (fd == 0) {
                    fgets(received_buffer, MAX_COMMAND_SIZE, stdin);
                    received_buffer[strlen(received_buffer) - 1] = '\0';
                    cout << "received command: " << received_buffer << endl;
                    handle_command(string(received_buffer));
                }

                // Receive connection message.
                else if (fd == server_pipe_fd) {
                    read(fd, received_buffer, MAX_MESSAGE_SIZE);
                    handle_connection_message(string(received_buffer));
                }

                // Receive message from clients.
                else {
                    read(fd, received_buffer, MAX_MESSAGE_SIZE);
                    cout << "client message: " << received_buffer << endl;
                    handle_client_message(string(received_buffer), clients_fds[fd]);
                }

                // // Receive message from group servers.
                // else if (find(groupservers_fds.begin(), groupservers_fds.end(), fd) != groupservers_fds.end()) {
                //     read(fd, received_buffer, MAX_MESSAGE_SIZE);
                //     cout << "group server message: " << received_buffer << endl;
                //     handle_groupservers_message(string(received_buffer));
                // }
            }
        }

        close_clients_fds(clients_fds);
        close_groupservers_fds(groupservers_fds);
        cout << "--------------- event ---------------" << endl;
    }

    close(server_pipe_fd);
}

map<int, string> Server::add_clients_to_set(fd_set& fds, int& max_fd) {
    map<int, string> clients_fds;
    map<string, pair<string, string>>::iterator it;
    for (it = clients_pipes.begin(); it != clients_pipes.end(); it++) {
        int client_fd = open(it->second.second.c_str(), O_RDWR);
        clients_fds.insert({client_fd, it->first});
        FD_SET(client_fd, &fds);
        max_fd = (max_fd > client_fd) ? max_fd : client_fd;
    }

    return clients_fds;
}

map<int, string> Server::add_groupservers_to_set(fd_set& fds, int& max_fd) {
    map<int, string> groupservers_fds;
    map<string, pair<string, string>>::iterator it;
    for (it = group_servers_pipes.begin(); it != group_servers_pipes.end(); it++) {
        int groupserver_fd = open(it->second.second.c_str(), O_RDWR);
        groupservers_fds.insert({groupserver_fd, it->first});
        FD_SET(groupserver_fd, &fds);
        max_fd = (max_fd > groupserver_fd) ? max_fd : groupserver_fd;
    }

    return groupservers_fds;
}


void Server::close_clients_fds(map<int, string> clients_fds){
    map<int, string>::iterator it;
    for (it = clients_fds.begin(); it != clients_fds.end(); it++)
        close(it->first);
}

void Server::close_groupservers_fds(map<int, string> groupservers_fds){
    map<int, string>::iterator it;
    for (it = groupservers_fds.begin(); it != groupservers_fds.end(); it++)
        close(it->first);
}

void Server::handle_command(string command) {
    vector<string> command_parts = split(command, COMMAND_DELIMITER);

    if (command_parts.size() < 1)
        return;

    if (command_parts[ARG0] == SERVER_TO_ROUTER_CONNECT_CMD)
        handle_connect_router(command_parts[ARG1]);

    else printf("Unknown command.\n");
}

void Server::handle_connect_router(string router_port) {

}

void Server::handle_connection_message(string message) {
    vector<string> message_parts = split(message, MESSAGE_DELIMITER);
    if (message_parts[ARG0] == CLIENT_TO_SERVER_CONNECT_MSG)
        handle_client_connect(message_parts[ARG1]);

    if (message_parts[ARG0] == GROUPSERVER_TO_SERVER_CONNECT_MSG)
        handle_group_server_connect(message_parts[ARG1], message_parts[ARG2]);
}

void Server::handle_client_connect(string name) {
    printf("Client with name %s connects.\n", name.c_str());

    pair<string, string> client_pipe = {(string(PIPE_ROOT_PATH) + SERVER_PIPE + CLIENT_PIPE + PIPE_NAME_DELIMITER + name + READ_PIPE),
            (string(PIPE_ROOT_PATH) + SERVER_PIPE + CLIENT_PIPE + PIPE_NAME_DELIMITER + name + WRITE_PIPE)};

    unlink(client_pipe.first.c_str());
	mkfifo(client_pipe.first.c_str(), READ_WRITE);
    unlink(client_pipe.second.c_str());
	mkfifo(client_pipe.second.c_str(), READ_WRITE);

    clients_pipes.insert({name, client_pipe});
}

void Server::handle_group_server_connect(string name, string ip) {
    printf("Group server with name %s and ip %s connects.\n", name.c_str(), ip.c_str());

    pair<string, string> group_server_pipe = {(string(PIPE_ROOT_PATH) + SERVER_PIPE + GROUPSERVER_PIPE + PIPE_NAME_DELIMITER + PIPE_NAME_DELIMITER + name + READ_PIPE),
            (string(PIPE_ROOT_PATH) + SERVER_PIPE + GROUPSERVER_PIPE + PIPE_NAME_DELIMITER + name + WRITE_PIPE)};

    unlink(group_server_pipe.first.c_str());
	mkfifo(group_server_pipe.first.c_str(), READ_WRITE);
    unlink(group_server_pipe.second.c_str());
	mkfifo(group_server_pipe.second.c_str(), READ_WRITE);

    group_servers_pipes.insert({name, group_server_pipe});
    groups_ip.insert({name, ip});
}

void Server::handle_client_message(string message, string client_name) {
    vector<string> message_parts = split(message, MESSAGE_DELIMITER);

    if (message_parts[ARG0] == GET_GROUP_LIST_MSG)
        handle_get_group_list(client_name);

    else printf("Unknown Message\n");
}

void Server::handle_get_group_list(string client_name) {
    string group_list = "Group List: ";
    map<string, string>::iterator it;
    for (it = groups_ip.begin(); it != groups_ip.end(); it++)
        group_list += "(" + it->first + ", " + it->second + ") ";
    
    int client_fd = open(clients_pipes[client_name].first.c_str(), O_RDWR);
    write(client_fd, group_list.c_str(), group_list.size());
    close(client_fd);
}

void Server::handle_groupservers_message(string message) {

}
