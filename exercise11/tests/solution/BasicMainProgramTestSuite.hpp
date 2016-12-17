#pragma once

#include "ModuleTestConfig.hpp"
#include "MessageReceiverMock.hpp"
#include "MessageSenderMock.hpp"
#include "UserOutputMock.hpp"
#include "TimerManagerMock.hpp"
#include "MessageFactoryFunctions.hpp"
#include <DataHolder.hpp>
#include <Commands.hpp>
#include <MainProgram.hpp>
#include <list>

using namespace testing;

namespace tests
{
struct BasicMainProgramTestSuite : public Test
{
    BasicMainProgramTestSuite()
        :   holder(std::make_shared<solution::DataHolder>()),
            receiverMock(std::make_shared<MessageReceiverMock>()),
            senderMock(std::make_shared<MessageSenderMock>()),
            userOutputMock(std::make_shared<NiceMock<UserOutputMock>>()),
            timerManagerMock(std::make_shared<NiceMock<TimerManagerMock>>()),
            out(createCommands(holder, receiverMock, senderMock, userOutputMock, timerManagerMock),
                                holder,
                                receiverMock,
                                senderMock,
                                userOutputMock,
                                timerManagerMock)
    {
        addMessageToQueue(createExitMessage());
        static std::set<framework::Identity> s_set;
        DefaultValue<const std::set<framework::Identity>&>::Set(s_set);
    }
 
    ~BasicMainProgramTestSuite()
    {
	
        DefaultValue<const std::set<framework::Identity>&>::Clear();
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
    std::shared_ptr<solution::DataHolder> holder;
    std::shared_ptr<MessageReceiverMock> receiverMock;
    std::shared_ptr<MessageSenderMock> senderMock;
    std::shared_ptr<UserOutputMock> userOutputMock;
    std::shared_ptr<TimerManagerMock> timerManagerMock;
    solution::MainProgram out;
};
}
