#include "../include/Client.h"

using namespace std;

int main(int argc, char* argv[]) {
    Client client(argv[1], argv[2], argv[3], argv[4]);
    client.start();
    return 0;
}

Client::Client(string name, string server_ip, string router_ip, string router_port)
: name(name)
, server_ip(server_ip)
, router_ip(router_ip)
, router_port(router_port) {
}

void Client::start() {

}
