#include "IncomingConnection.hpp"
#include <netinet/ip.h>
#include <unistd.h>
#include <Utilities.hpp>
#include <MessageTypes.hpp>
#include <InternalQueue.hpp>
#include "OutgoingConnection.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <iostream>
#include <errno.h>

namespace framework
{

void IncomingConnection::run()
{
    connect();

    while (1)
    {
        const char * message = receive();
        if (running)
        {
            queue->send(message);
        }
        else
        {
            return;
        }
    }
}

void IncomingConnection::stop()
{
    running = false;
    OutgoingConnection connection (port);
    std::string dummy = "dummy";
    connection.send(dummy);
}

const char * IncomingConnection::receive()
{
    int address {};
    return receive(address);
}

const char * IncomingConnection::receive(int& address)
{
    char * data = new char[BUFFER_SIZE+1];
    sockaddr_in sender_address = {};
    socklen_t addressLength = sizeof(sender_address);

    size_t length = recvfrom(socketId, data + 1, BUFFER_SIZE, 0, (sockaddr*)&sender_address, &addressLength);

    address = sender_address.sin_addr.s_addr;
    data[0] = static_cast<char>(MessageType::EXTERNAL);
    data[length+1] = 0;
    return data;
}

void IncomingConnection::setTimeout(int seconds, int microseconds)
{
    timeval tv{};
    tv.tv_sec = seconds;
    tv.tv_usec = microseconds;
    int err = setsockopt(socketId, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv));
    if ( err < 0)
    {
        std::cout << "Error " << errno << std::endl;
      //error;
    }
}

IncomingConnection::IncomingConnection(int port, std::shared_ptr<InternalQueue> queue)
    : port(port),
      socketId(0),
      queue(queue),
      running(true)
{

}

IncomingConnection::~IncomingConnection()
{
    close(socketId);
}

void IncomingConnection::connect()
{
    struct sockaddr_in socket_address = {};
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);

    socketId = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    //if socketId == -1 throw
    bind(socketId, (const sockaddr*)&socket_address, sizeof(socket_address));
    //if bind returns -1 throw
}
}
