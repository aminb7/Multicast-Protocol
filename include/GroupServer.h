#include <string>

class GroupServer
{
public:
    GroupServer(std::string group_name, std::string server_ip);
    ~GroupServer() = default;

    void start();

private:
    std::string group_name;
    std::string server_ip;
};
