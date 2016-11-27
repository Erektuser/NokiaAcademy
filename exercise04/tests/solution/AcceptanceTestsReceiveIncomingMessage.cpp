#include "BasicMainProgramTestSuite.hpp"
#include <string>

namespace tests
{

struct AcceptanceTests_ReceiveIncomingMessage : public BasicMainProgramTestSuite
{
    void addIncomingTextMessage(const std::string& message)
    {
        EXPECT_CALL(*userOutputMock, print(EndsWith(message)));
        addMessageToQueue(createIncomingTextMessage(0,message));
    }
};

TEST_F(AcceptanceTests_ReceiveIncomingMessage, handleIncomingTextMessage)
{
    addIncomingTextMessage("Hello World!");
    out.run();
}

TEST_F(AcceptanceTests_ReceiveIncomingMessage, handleMultipleIncomingTextMessages)
{
    addIncomingTextMessage("Hi");
    addIncomingTextMessage("How are you?");
    addIncomingTextMessage("Do you want to code?");
    out.run();
}

}
