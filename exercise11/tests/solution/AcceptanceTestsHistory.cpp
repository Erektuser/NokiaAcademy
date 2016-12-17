#include "BasicMainProgramTestSuite.hpp"
#include "MessageFactoryFunctions.hpp"
#include <string>

namespace tests
{

struct AcceptanceTests_History : public BasicMainProgramTestSuite
{
    void addIncomingTextMessage(const std::string& message)
    {
        std::string expected = "[unknown] " + message;
        EXPECT_CALL(*userOutputMock, print(StrEq(expected)));
        addMessageToQueue(createIncomingTextMessage(0,message));
    }
};

static const char* name = "<user name>";

TEST_F(AcceptanceTests_History, handleUserSelectionMessage)
{
    std::string msg1 = "Msg1";
    std::string msg2 = "Msg2";

    addMessageToQueue(createUserSelectionMessage(name));
    addMessageToQueue(createExternalUserInfoResponseMessage(1, name));
    addMessageToQueue(createIncomingTextMessage(1, msg2));
    addMessageToQueue(createIncomingTextMessage(0, msg1));

    {
        InSequence s;

        EXPECT_CALL(*userOutputMock, print(EndsWith(msg1)));
        EXPECT_CALL(*userOutputMock, clearOutput());
        EXPECT_CALL(*userOutputMock, print(EndsWith(msg2)));
    }
    out.run();
}

TEST_F(AcceptanceTests_History, handleAddToHistory)
{

   std::string msg0 = "Msg1";
   std::string msg1 = "Msg2";

   addMessageToQueue(createIncomingTextMessage(1,msg1));
   addMessageToQueue(createIncomingTextMessage(0,msg0));

   {
       EXPECT_CALL(*userOutputMock, print(EndsWith(msg0)));
   }


   out.run();
}

}
