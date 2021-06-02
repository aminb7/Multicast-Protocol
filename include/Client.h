#include <string>

class Client
{
public:
    Client(std::string name, std::string server_ip, std::string router_ip,
            std::string router_port);
    ~Client() = default;

    void start();
private:

    std::string name;
    std::string server_ip;
    std::string router_ip;
    std::string router_port;
};
