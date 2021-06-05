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
                    cin >> received_buffer;
                    cout << "received command: " << received_buffer << endl;
                    handle_command(string(received_buffer));
                }

                // Receive connection message.
                else if (fd == server_pipe_fd) {
                    read(fd, received_buffer, MAX_MESSAGE_SIZE);
                    handle_network_message(string(received_buffer));
                }
            }
        }

        cout << "--------------- event ---------------" << endl;
    }
    close(server_pipe_fd);
}

void Server::handle_command(string command) {

}

void Server::handle_network_message(string message) {
    vector<string> message_parts = split(message, MESSAGE_DELIMITER);
    if (message_parts[ARG0] == CLIENT_TO_SERVER_CONNECT_MSG)
        handle_client_connect(message_parts[ARG1]);

    if (message_parts[ARG0] == GROUPSERVER_TO_SERVER_CONNECT_MSG)
        handle_group_server_connect(message_parts[ARG1]);
}

void Server::handle_client_connect(string name) {
    printf("Client with name %s connects\n", name.c_str());

    pair<string, string> client_pipe = {(string(PIPE_ROOT_PATH) + SERVER_PIPE + CLIENT_PIPE + name + READ_PIPE),
            (string(PIPE_ROOT_PATH) + SERVER_PIPE + CLIENT_PIPE + name + WRITE_PIPE)};

    unlink(client_pipe.first.c_str());
	mkfifo(client_pipe.first.c_str(), READ_WRITE);
    unlink(client_pipe.second.c_str());
	mkfifo(client_pipe.second.c_str(), READ_WRITE);

    clients_pipes.insert({name, client_pipe});
}

void Server::handle_group_server_connect(string name) {
    printf("Group server with name %s connects\n", name.c_str());

    pair<string, string> group_server_pipe = {(string(PIPE_ROOT_PATH) + SERVER_PIPE + GROUPSERVER_PIPE + name + READ_PIPE),
            (string(PIPE_ROOT_PATH) + SERVER_PIPE + GROUPSERVER_PIPE + name + WRITE_PIPE)};

    unlink(group_server_pipe.first.c_str());
	mkfifo(group_server_pipe.first.c_str(), READ_WRITE);
    unlink(group_server_pipe.second.c_str());
	mkfifo(group_server_pipe.second.c_str(), READ_WRITE);

    group_servers_pipes.insert({name, group_server_pipe});
}
