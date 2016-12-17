#pragma once

#include <string>
#include <set>
#include "Identity.hpp"

namespace framework
{
class IMessageSender
{
public:
    virtual ~IMessageSender() {}

    virtual void sendTo(Identity address, int size, const char * message) = 0;
    virtual const std::set<Identity>& getAddresses() = 0;
};

}
