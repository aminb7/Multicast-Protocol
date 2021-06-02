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

}
