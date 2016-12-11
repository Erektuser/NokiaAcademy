#pragma once

#include <gmock/gmock.h>
#include <IMessageReceiver.hpp>

namespace tests
{
struct MessageReceiverMock : public framework::IMessageReceiver
{
    MOCK_METHOD0(receive, const char * ());
};
}
