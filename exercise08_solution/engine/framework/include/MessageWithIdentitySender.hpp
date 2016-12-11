#pragma once

#include "IMessageSender.hpp"
#include <memory>

namespace framework
{
class MessageWithIdentitySender : public IMessageSender
{
public:
    MessageWithIdentitySender(std::shared_ptr<IMessageSender> sender);

    void sendTo(Identity address, int size, const char * message) override;
    const std::set<Identity>& getAddresses() override;
private:
    std::shared_ptr<IMessageSender> sender;
};
}
