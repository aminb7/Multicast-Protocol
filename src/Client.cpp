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
}

void Client::start() {
    fd_set read_fds, copy_fds;
    FD_ZERO(&copy_fds);
    FD_SET(STDIN, &copy_fds);
    int max_fd = STDIN;
    int activity;
    char received_buffer[MAX_MESSAGE_SIZE] = {0};
    printf("Client is starting ...\n");
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

void Client::handle_command(string command) {

}

void Client::handle_pip_message(string pipe_message) {
    
}
