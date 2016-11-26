#pragma once

#include "ModuleTestConfig.hpp"
#include "MessageReceiverMock.hpp"
#include "MessageSenderMock.hpp"
#include "UserOutputMock.hpp"
#include "TimerManagerMock.hpp"
#include "MessageFactoryFunctions.hpp"
#include <MainProgram.hpp>
#include <list>

using namespace testing;

namespace tests
{
struct BasicMainProgramTestSuite : public Test
{
    BasicMainProgramTestSuite()
        : receiverMock(std::make_shared<MessageReceiverMock>()),
          senderMock(std::make_shared<NiceMock<MessageSenderMock>>()),
          userOutputMock(std::make_shared<NiceMock<UserOutputMock>>()),
          timerManagerMock(std::make_shared<TimerManagerMock>()),
          out(receiverMock, senderMock, userOutputMock, timerManagerMock)
    {
        addMessageToQueue(createExitMessage());
    }

    void addMessageToQueue(const char * message)
    {
        EXPECT_CALL(*receiverMock, receive()).WillOnce(Return(message)).RetiresOnSaturation();
    }

    std::shared_ptr<MessageReceiverMock> receiverMock;
    std::shared_ptr<NiceMock<MessageSenderMock>> senderMock;
    std::shared_ptr<NiceMock<UserOutputMock>> userOutputMock;
    std::shared_ptr<TimerManagerMock> timerManagerMock;
    solution::MainProgram out;
};
}
