#include "../include/Client.h"

using namespace std;

int main(int argc, char* argv[]) {
    Client client(argv[1], argv[2], argv[3], argv[4]);
    client.start();
    return 0;
}

Client::Client(string name, string server_ip, string router_ip, string router_port)
: client_ip(LOCAL_IP)
, client_port(8081)
, name(name)
, server_ip(server_ip)
, router_ip(router_ip)
, router_port(router_port) {
    // Send connection message to server.
    string server_pipe = PIPE_ROOT_PATH + string(server_ip) + READ_PIPE;
    int server_pipe_fd = open(server_pipe.c_str(), O_RDWR);
    string connect_message = string(CLIENT_TO_SERVER_CONNECT_MSG) + MESSAGE_DELIMITER + name;
    write(server_pipe_fd, connect_message.c_str(), connect_message.size());
    close(server_pipe_fd);

    client_to_server_pipe = {(string(PIPE_ROOT_PATH) + SERVER_PIPE + CLIENT_PIPE + name + READ_PIPE),
            (string(PIPE_ROOT_PATH) + SERVER_PIPE + CLIENT_PIPE + name + WRITE_PIPE)};
}

void Client::start() {
    fd_set read_fds, copy_fds;
    FD_ZERO(&copy_fds);
    FD_SET(STDIN, &copy_fds);
    int max_fd = STDIN;
    int activity;
    char received_buffer[MAX_MESSAGE_SIZE] = {0};
    while (true) {
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

                // // Network pip message
                // else if (fd == network_pipe_write_fd) {
                //     read(fd, received_buffer, MAX_MESSAGE_SIZE);
                //     cout << "received network message: " << received_buffer << endl;
                // }

                // Pipe pipe message
                else {
                    read(fd, received_buffer, MAX_MESSAGE_SIZE);
                    cout << "received pipe message: " << received_buffer << endl;
                    handle_pip_message(string(received_buffer));
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

    if (command_parts[ARG0] == SET_CLIENT_IP_CMD)
        handle_set_ip(command_parts[ARG1]);

    if (command_parts[ARG0] == GET_GROUP_LIST_CMD)
        handle_get_group_list();

    if (command_parts[ARG0] == JOIN_GROUP_CMD)
        handle_join_group(command_parts[ARG1]);

    if (command_parts[ARG0] == LEAVE_GROUP_CMD)
        handle_leave_group(command_parts[ARG1]);

    if (command_parts[ARG0] == SELECT_GROUP_CMD)
        handle_select_group(command_parts[ARG1]);

    if (command_parts[ARG0] == SEND_FILE_CMD)
        handle_send_file(command_parts[ARG1], command_parts[ARG2]);

    if (command_parts[ARG0] == SEND_MESSAGE_CMD)
        handle_send_message(command_parts[ARG1], command_parts[ARG2]);

    if (command_parts[ARG0] == SHOW_GROUPS_CMD)
        handle_show_groups();

    if (command_parts[ARG0] == SYNC_CMD)
        handle_sync();

    if (command_parts[ARG0] == SIGN_OUT_CMD)
        handle_sign_out();

    else printf("Unknown command.\n");
}

void Client::handle_set_ip(string ip) {

}

void Client::handle_get_group_list() {

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
