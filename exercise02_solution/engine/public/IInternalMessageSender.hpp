#pragma once

#include <string>

namespace framework
{
class IInternalMessageSender
{
public:
    virtual ~IInternalMessageSender() {}

    virtual void sendExitMessage() = 0;
    virtual void sendTextMessage(std::string& text) = 0;
    virtual void sendSetRecipient(std::string& name) = 0;
};
}
