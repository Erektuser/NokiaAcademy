#pragma once

#include <gmock/gmock.h>
#include <IMessageSender.hpp>

namespace tests
{
struct MessageSenderMock : public framework::IMessageSender
{
    MOCK_METHOD3(sendTo, void (framework::Identity address, int size, const char * message));
    MOCK_METHOD0(getAddresses, const std::set<framework::Identity>& ());
};
}
