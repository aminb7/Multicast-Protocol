#include "../include/GroupServer.h"

using namespace std;

int main(int argc, char* argv[]) {
    GroupServer group_server(argv[1], argv[2]);
    group_server.start();
    return 0;
}

GroupServer::GroupServer(string group_name, string server_ip)
: group_name(group_name)
, server_ip(server_ip) {
}

void GroupServer::start() {
    fd_set read_fds, copy_fds;
    FD_ZERO(&copy_fds);
    FD_SET(STDIN, &copy_fds);
    int max_fd = STDIN;
    int activity;
    char received_buffer[MAX_MESSAGE_SIZE] = {0};
    printf("Group server is starting ...\n");
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
                    cin >> received_buffer;
                    cout << "received command: " << received_buffer << endl;
                    handle_command(string(received_buffer));
                }

                // Pipe. input
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

void GroupServer::handle_command(string command) {

}

void GroupServer::handle_pip_message(string pipe_message) {
    
}
