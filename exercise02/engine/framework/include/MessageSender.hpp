#pragma once

#include "IMessageSender.hpp"
#include "OutgoingConnection.hpp"
#include "Identity.hpp"
#include <map>
#include <memory>
#include <initializer_list>
#include <utility>
#include <string>
#include <mutex>

namespace framework
{
using Connection = std::shared_ptr<OutgoingConnection>;

class MessageSender : public IMessageSender
{
public:
    MessageSender();
    void sendTo(Identity address, int size, const char * message) override;
    const std::set<Identity>& getAddresses() override;
    void addRecipient(Identity identity, int address, int port);
    void sendToAll(int size, const char * message);

private:
    void send(Identity address, int size, const char * message);
    void addConnection(Identity identity, std::shared_ptr<OutgoingConnection> connection);
    std::map<Identity, Connection> connectionMap;
    std::set<Identity> addresses;
    std::mutex mutex;
};
}
