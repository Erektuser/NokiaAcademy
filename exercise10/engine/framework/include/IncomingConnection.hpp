#pragma once

#include "IService.hpp"
#include <string>
#include <memory>

namespace framework
{
struct InternalQueue;

class IncomingConnection : public IService
{
public:
    IncomingConnection(int port, std::shared_ptr<InternalQueue> queue);
    ~IncomingConnection();
    void connect();
    void run() override;
    void stop() override;
    const char * receive();
    void setTimeout(int seconds, int microseconds = 0);
    const char *receive(int &address);
private:
    const int port;
    int socketId;
    std::shared_ptr<InternalQueue> queue;
    bool running;
    static const int BUFFER_SIZE = 2048;

};
}
