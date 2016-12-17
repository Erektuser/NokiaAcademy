#pragma once

#include <string>
#include <netinet/ip.h>
#include <IOutgoingConnection.hpp>
#include <tuple>

namespace framework
{
class OutgoingConnection : public IOutgoingConnection
{
public:
    OutgoingConnection(int port);
    OutgoingConnection(int address, int port);
    ~OutgoingConnection();
    void send (const std::string& message) override;
    void send(int size, const char *) override;
private:
    int socketId;
    sockaddr_in addressInfo;
};
}
