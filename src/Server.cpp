#include "../include/Server.h"

using namespace std;

int main(int argc, char* argv[]) {
    Server server(argv[1]);
    server.start();
    return 0;
}

Server::Server(string server_ip)
: server_ip(server_ip) {
}

void Server::start() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        return;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(server_ip.c_str());
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
        return;

    constexpr int backlog = 10;
    if (listen(server_fd, backlog) < 0)
        return;

    fd_set read_fds, copy_fds;
    FD_ZERO(&copy_fds);
    FD_SET(0, &copy_fds);
    // FD_SET(server_fd, &copy_fds);
    int max_fd = server_fd;
    int activity;
    char received_buffer[128] = {0};

    printf("server is starting ...\n");
    while (true) {
        // Add sockets to list
        memcpy(&read_fds, &copy_fds, sizeof(copy_fds));

        // Select
        activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (activity < 0)
            return;

        int ready_sockets = activity;
        for (int fd = 0; fd <= max_fd  &&  ready_sockets > 0; ++fd) {
            if (FD_ISSET(fd, &read_fds)) {
                // New connection.
                if (fd == server_fd) {
                    int new_socket = accept(server_fd, NULL, NULL);
                    if (new_socket < 0)
                        return;

                    FD_SET(new_socket, &copy_fds);
                    if (new_socket > max_fd)
                        max_fd = new_socket;
                }

                else if (fd == 0) {
                    memset(received_buffer, 0, sizeof received_buffer);
                    fgets(received_buffer, sizeof(received_buffer), stdin);
                    cout << "received message: " << received_buffer << endl;
                }

                // New readable socket.
                else {
                    bool close_connection = false;
                    memset(received_buffer, 0, sizeof received_buffer);
                    int result = recv(fd, received_buffer, sizeof(received_buffer), 0);

                    if (result < 0)
                        if (errno != EWOULDBLOCK)
                            close_connection = true;

                    // Check to see if the connection has been closed by client.
                    if (result == 0)
                        close_connection = 1;

                    // Data is received.
                    if (result > 0) {
                        // handle command
                    }

                    if (close_connection) {
                        close(fd);
                        FD_CLR(fd, &copy_fds);
                        if (fd == max_fd)
                            while (FD_ISSET(max_fd, &copy_fds) == 0)
                                max_fd -= 1;
                    }
                }
            }
        }
    }
}
