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
          senderMock(std::make_shared<MessageSenderMock>()),
          userOutputMock(std::make_shared<UserOutputMock>()),
          timerManagerMock(std::make_shared<TimerManagerMock>()),
          out(receiverMock, senderMock, userOutputMock, timerManagerMock)
    {
        addMessageToQueue(createExitMessage());
    }

    void addMessageToQueue(const char * message)
    {
        EXPECT_CALL(*receiverMock, receive()).WillOnce(Return(message)).RetiresOnSaturation();
    }
    void addTimerExpirationMessage(unsigned int id)
    {
        addMessageToQueue(createTimerExpirationMessage(id));
    }
    void addUserSelectionMessage(const std::string & message)
    {
        addMessageToQueue(createUserSelectionMessage(message));
    }
    std::shared_ptr<MessageReceiverMock> receiverMock;
    std::shared_ptr<MessageSenderMock> senderMock;
    std::shared_ptr<UserOutputMock> userOutputMock;
    std::shared_ptr<TimerManagerMock> timerManagerMock;
    solution::MainProgram out;
};
}
