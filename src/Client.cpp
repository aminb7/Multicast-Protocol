#include "../include/Client.h"

using namespace std;

int main(int argc, char* argv[]) {
    Client client(argv[1], argv[2], argv[3], argv[4]);
    client.start();
    return 0;
}

Client::Client(string name, string server_ip, string router_ip, string router_port)
: client_ip(DEFALAUT_IP)
, client_port(8081)
, name(name)
, server_ip(server_ip)
, router_ip(router_ip)
, router_port(router_port) {
    // Send connection message to server.
    string server_pipe = PIPE_ROOT_PATH + string(server_ip) + READ_PIPE;
    int server_pipe_fd = open(server_pipe.c_str(), O_RDWR);
    string server_connect_message = string(CLIENT_TO_SERVER_CONNECT_MSG) + MESSAGE_DELIMITER + name;
    write(server_pipe_fd, server_connect_message.c_str(), server_connect_message.size());
    close(server_pipe_fd);

    client_to_server_pipe = {(string(PIPE_ROOT_PATH) + SERVER_PIPE + CLIENT_PIPE + PIPE_NAME_DELIMITER + name + READ_PIPE),
            (string(PIPE_ROOT_PATH) + SERVER_PIPE + CLIENT_PIPE + PIPE_NAME_DELIMITER + name + WRITE_PIPE)};

    // Send connection message to router.
    string router_pipe = PIPE_ROOT_PATH + string(router_port);
    int router_pipe_fd = open(router_pipe.c_str(), O_RDWR);
    string router_connect_message = string(CLIENT_MESSAGE_PREFIX) + MESSAGE_DELIMITER
            + string("connect") + MESSAGE_DELIMITER + client_ip;
    write(router_pipe_fd, router_connect_message.c_str(), router_connect_message.size());
    close(router_pipe_fd);
    client_to_router_pipe = {(string(PIPE_ROOT_PATH) + ROUTER_PIPE + CLIENT_PIPE + PIPE_NAME_DELIMITER + client_ip + READ_PIPE),
            (string(PIPE_ROOT_PATH) + ROUTER_PIPE + CLIENT_PIPE + PIPE_NAME_DELIMITER + client_ip + WRITE_PIPE)};
}

void Client::start() {
    fd_set read_fds, copy_fds;
    FD_ZERO(&copy_fds);
    FD_SET(STDIN, &copy_fds);
    int max_fd = STDIN;
    int activity;
    char received_buffer[MAX_MESSAGE_SIZE] = {0};
    while (true) {
        int router_pipe_fd = open(client_to_router_pipe.first.c_str(), O_RDWR);
        FD_SET(router_pipe_fd, &copy_fds);
        max_fd = router_pipe_fd;

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

                // Command line input
                if (fd == 0) {
                    fgets(received_buffer, MAX_COMMAND_SIZE, stdin);
                    received_buffer[strlen(received_buffer) - 1] = '\0';
                    cout << "received command: " << received_buffer << endl;
                    handle_command(string(received_buffer));
                }

                // Router message
                if (fd == router_pipe_fd) {
                    read(fd, received_buffer, MAX_MESSAGE_SIZE);
                    cout << "received router message: " << received_buffer << endl;
                }
            }
        }

        cout << "--------------- event ---------------" << endl;
    }
}

void Client::handle_command(string command) {
    vector<string> command_parts = split(command, COMMAND_DELIMITER);

    if (command_parts.size() < 1)
        return;

    else if (command_parts[ARG0] == SET_CLIENT_IP_CMD)
        handle_set_ip(command_parts[ARG1]);

    else if (command_parts[ARG0] == GET_GROUP_LIST_CMD)
        handle_get_group_list();

    else if (command_parts[ARG0] == JOIN_GROUP_CMD)
        handle_join_group(command_parts[ARG1]);

    else if (command_parts[ARG0] == LEAVE_GROUP_CMD)
        handle_leave_group(command_parts[ARG1]);

    else if (command_parts[ARG0] == SELECT_GROUP_CMD)
        handle_select_group(command_parts[ARG1]);

    else if (command_parts[ARG0] == SEND_FILE_CMD)
        handle_send_file(command_parts[ARG1], command_parts[ARG2]);

    else if (command_parts[ARG0] == SEND_MESSAGE_CMD)
        handle_send_message(command_parts[ARG1], command_parts[ARG2]);

    else if (command_parts[ARG0] == SHOW_GROUPS_CMD)
        handle_show_groups();

    else if (command_parts[ARG0] == SYNC_CMD)
        handle_sync();

    else if (command_parts[ARG0] == SIGN_OUT_CMD)
        handle_sign_out();

    else printf("Unknown command.\n");
}

void Client::handle_set_ip(string ip) {
    this->client_ip = ip;
    printf("Client IP changed successfuly\n");
}

void Client::handle_get_group_list() {
    int pipe_write_fd = open(client_to_server_pipe.second.c_str(), O_RDWR);
    string message = string(GET_GROUP_LIST_MSG);
    write(pipe_write_fd, message.c_str(), message.size());
    close(pipe_write_fd);

    char group_list[MAX_MESSAGE_SIZE] = {0};
    memset(group_list, 0, sizeof group_list);
    int pipe_read_fd = open(client_to_server_pipe.first.c_str(), O_RDWR);
    read(pipe_read_fd, group_list, MAX_MESSAGE_SIZE);
    close(pipe_read_fd);

    cout << group_list << endl;
}

void Client::handle_join_group(string group_name) {

}

void Client::handle_leave_group(string group_name) {

}

void Client::handle_select_group(string group_name) {

}

void Client::handle_send_file(string file_name, string group_name) {

}

void Client::handle_send_message(string message, string group_name) {

}

void Client::handle_show_groups() {

}

void Client::handle_sync() {

}

void Client::handle_sign_out() {

}

void Client::handle_pip_message(string pipe_message) {
    
}
