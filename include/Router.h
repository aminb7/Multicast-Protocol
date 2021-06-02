#include <string>

class Router
{
public:
    Router(std::string listen_port);
    ~Router() = default;

    void start();

private:
    std::string listen_port;
};
