#pragma once

#include "IInternalMessageSender.hpp"
#include <memory>

namespace framework
{
struct InternalQueue;

class InternalMessageSender : public IInternalMessageSender
{
public:
    InternalMessageSender(std::shared_ptr<InternalQueue> queue)
        : queue(queue)
    {}
    void sendExitMessage() override;
    void sendTextMessage(std::string& text) override;
    void sendSetRecipient(std::string& name) override;
    void sendTimerExpiredMessage(int timerId);
private:
    std::shared_ptr<InternalQueue> queue;
};
}
