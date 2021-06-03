#include "../include/Network.h"

using namespace std;

int main() {
    Network network;
    network.start();
    return 0;
}

Network::Network()
: network_pipe(PIPE_ROOT_PATH + string(NETWORK_PIPE_NAME)) {
    unlink(network_pipe.c_str());
	mkfifo(network_pipe.c_str(), READ_WRITE);
}

void Network::start() {
    
    char received_message[] = {0};
    fd_set fds;
    int maxfd;
    while (true) {
        int network_pipe_fd = open(network_pipe.c_str(), O_RDWR);
        maxfd = network_pipe_fd;
        FD_ZERO(&fds);
        FD_SET(network_pipe_fd, &fds);

        if (select(maxfd + 1, &fds, NULL, NULL, NULL) < 0)
            return;

        if (FD_ISSET(network_pipe_fd, &fds)) {
            memset(received_message, 0, sizeof received_message);
            read(network_pipe_fd, received_message, MAX_MESSAGE_SIZE);
            handle_network_message(received_message);
        }

        close(network_pipe_fd);
    }
}

void Network::handle_network_message(string message) {

}
