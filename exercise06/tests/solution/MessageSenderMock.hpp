#pragma once

#include <gmock/gmock.h>
#include <IMessageSender.hpp>
#include <vector>

namespace tests
{
struct MessageSenderMock : public framework::IMessageSender
{
    void sendTo(framework::Identity address, int size, const char * message)
    {
        std::vector<char> vec(message, message + size);
        sendTo(address, vec);
    }
    MOCK_METHOD2(sendTo, void (framework::Identity address, std::vector<char> data));
    MOCK_METHOD0(getAddresses, const std::set<framework::Identity>& ());
};
}
