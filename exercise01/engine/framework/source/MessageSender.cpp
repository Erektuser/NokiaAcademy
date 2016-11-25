#include "MessageSender.hpp"
#include "OutgoingConnection.hpp"
#include <utility>

namespace framework
{
MessageSender::MessageSender()
    :connectionMap(),
     addresses(),
     mutex()
{
}

void MessageSender::sendTo(Identity address, int size, const char * message)
{
    std::lock_guard<std::mutex> guard(mutex);
    send(address, size, message);
}

const std::set<Identity>& MessageSender::getAddresses()
{
    std::lock_guard<std::mutex> guard(mutex);
    return addresses;
}

void MessageSender::addRecipient(Identity identity, int address, int port)
{
    std::lock_guard<std::mutex> guard(mutex);
    if (addresses.find(identity) == addresses.end())
    {
        addConnection(identity, std::make_shared<OutgoingConnection>(address, port));
    }
}

void MessageSender::sendToAll(int size, const char *message)
{
    std::lock_guard<std::mutex> guard(mutex);
    for (auto& address : addresses)
    {
        send(address, size, message);
    }
}

void MessageSender::send(Identity address, int size, const char *message)
{
    auto connectionIterator = connectionMap.find(address);
    if (connectionIterator != connectionMap.end())
    {
        connectionIterator->second->send(size, message);
    }
}

void MessageSender::addConnection(Identity identity, std::shared_ptr<OutgoingConnection> connection)
{
    connectionMap.insert(std::make_pair(identity, connection));
    addresses.insert(identity);
}
}

