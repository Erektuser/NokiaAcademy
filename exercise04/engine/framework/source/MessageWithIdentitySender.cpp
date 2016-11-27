#include "MessageWithIdentitySender.hpp"
#include <algorithm>
#include "MessageTypes.hpp"

namespace framework
{

MessageWithIdentitySender::MessageWithIdentitySender(std::shared_ptr<IMessageSender> sender)
    :sender(sender)
{
}

void MessageWithIdentitySender::sendTo(Identity address, int size, const char *message)
{
    OutgoingMessage outgoingMessage{};
    outgoingMessage.identity = getMyIdentity();
    char * data = (char *)&(outgoingMessage.message);
    std::copy(message, message + size, data);
    sender->sendTo(address, size + sizeof(Identity), (char *) &outgoingMessage);
}

const std::set<Identity> &MessageWithIdentitySender::getAddresses()
{
    return sender->getAddresses();
}

}
