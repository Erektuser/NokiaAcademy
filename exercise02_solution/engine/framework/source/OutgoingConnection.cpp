#include "OutgoingConnection.hpp"
#include <netdb.h>
#include <unistd.h>
#include "Utilities.hpp"
#include <tuple>
#include <atomic>
#include <map>

namespace framework
{
OutgoingConnection::OutgoingConnection(int port)
    : OutgoingConnection(getLocalAddess(), port)
{

}

OutgoingConnection::OutgoingConnection(int address, int port)
    :socketId(-1),
     addressInfo()
{
    socketId = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    addressInfo.sin_family = AF_INET;
    addressInfo.sin_port = htons(port);
    addressInfo.sin_addr.s_addr = address;
}

OutgoingConnection::~OutgoingConnection()
{
    close(socketId);
}

void OutgoingConnection::send(const std::string &message)
{
    send(message.size(), message.data());
}

void OutgoingConnection::send(int size, const char * message)
{
    sendto(socketId, message, size, 0, (sockaddr *) &addressInfo, sizeof(addressInfo));
}
}
