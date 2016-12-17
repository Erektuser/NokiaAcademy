#pragma once

#include <gmock/gmock.h>
#include <IMessageSender.hpp>
#include <vector>

namespace tests
{
struct MessageSenderMock : public framework::IMessageSender
{
    MOCK_METHOD3(sendTo, void(framework::Identity, int, const char *));
    MOCK_METHOD2(sendTo, void (framework::Identity address, std::vector<char> data));
    MOCK_METHOD0(getAddresses, const std::set<framework::Identity>& ());
};
}
