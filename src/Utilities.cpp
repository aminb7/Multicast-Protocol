#include "../include/Utilities.h"

using namespace std;

int create_socket(string ip, int port)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
        return -1;

    int opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        return -1;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip.c_str());
    address.sin_port = htons(port);

    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
        return -1;

    constexpr int backlog = 10;
    if (listen(socket_fd, backlog) < 0)
        return -1;

    return socket_fd;
}

vector<string> split(const string& s, char delimiter) {
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
      tokens.push_back(token);
   return tokens;
}

std::vector<std::pair<string, string>> store_csv_as_map(string filename) {
    std::ifstream fin(filename);

    std::vector<std::pair<string, string>> table;

    if (!fin) { 
        std::cout << "Error, could not open file." << std::endl; 
        return table;
    }

    std::string first, second;
    string comma = ",";
    while (fin >> first >> comma >> second) {
        table.push_back(make_pair(first, second));
    }

    fin.close();

    for (auto & row : table) {
        std::cout << row.first << " " << row.second << std::endl;
    }

    return table;
}
