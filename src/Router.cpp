#include "../include/Router.h"

using namespace std;

int main(int argc, char* argv[]) {
    Router router(argv[1]);
    router.start();
    return 0;
}

Router::Router(string listen_port)
: listen_port(listen_port) {
}

void Router::start() {
    fd_set read_fds, copy_fds;
    FD_ZERO(&copy_fds);
    FD_SET(STDIN, &copy_fds);
    int max_fd = STDIN;
    int activity;
    char received_buffer[MAX_MESSAGE_SIZE] = {0};
    string network_pipe_read = PIPE_ROOT_PATH + string(NETWORK_PIPE_NAME) + string(READ_PIPE);
    string network_pipe_write = PIPE_ROOT_PATH + string(NETWORK_PIPE_NAME) + string(WRITE_PIPE);
    printf("Router is starting ...\n");
    while (true) {
        int network_pipe_write_fd = open(network_pipe_write.c_str(), O_RDWR);
        max_fd = network_pipe_write_fd;
        FD_SET(network_pipe_write_fd, &copy_fds);

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

                // Network pip message
                else if (fd == network_pipe_write_fd) {
                    read(fd, received_buffer, MAX_MESSAGE_SIZE);
                    cout << "received network message: " << received_buffer << endl;
                }

                // Pipe pipe message
                else {
                    read(fd, received_buffer, MAX_MESSAGE_SIZE);
                    cout << "received pipe message: " << received_buffer << endl;
                    handle_pip_message(string(received_buffer));
                }
            }
        }

        close(network_pipe_write_fd);
        cout << "--------------- event ---------------" << endl;
    }
}

void Router::handle_command(string command) {
    vector<string> command_parts = split(command, COMMAND_DELIMITER);

    if (command_parts.size() < 1)
        return;

    if (command_parts[ARG0] == ROUTER_TO_ROUTER_CONNECT_CMD)
        handle_connect_router(command_parts[ARG1], command_parts[ARG2]);

    if (command_parts[ARG0] == CHANGE_COST_CMD)
        handle_change_cost(command_parts[ARG1], command_parts[ARG2]);

    if (command_parts[ARG0] == DISCONNECT_LINK_CMD)
        handle_disconnect(command_parts[ARG1]);

    if (command_parts[ARG0] == SHOW_CMD)
        handle_show();

    else printf("Unknown command.\n");
}

void Router::handle_connect_router(string router_port, string link) {

}

void Router::handle_change_cost(string link, string cost) {

}

void Router::handle_disconnect(string link) {

}

void Router::handle_show() {

}

void Router::handle_pip_message(string pipe_message) {
    
}
