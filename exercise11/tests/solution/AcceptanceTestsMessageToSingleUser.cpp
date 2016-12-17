#include "BasicMainProgramTestSuite.hpp"

namespace tests
{

struct AcceptanceTests_MessageToSingleUser : public BasicMainProgramTestSuite
{
};

TEST_F(AcceptanceTests_MessageToSingleUser, clearOutputUponUserSelection)
{
   addMessageToQueue(createUserSelectionMessage("1"));
   EXPECT_CALL(*userOutputMock, clearOutput());
   out.run();
}

TEST_F(AcceptanceTests_MessageToSingleUser, pickUpFirstUserWhenNoUserSelectedAndPrintMessage)
{
   std::string msg1 = "Msg1";
   addMessageToQueue(createIncomingTextMessage(0, msg1));
   EXPECT_CALL(*userOutputMock, print(EndsWith(msg1)));
   out.run();
}

TEST_F(AcceptanceTests_MessageToSingleUser, printMessageForSelectedUserOnly)
{
   std::string msg1 = "Msg1";
   std::string msg2 = "Msg2";

   addMessageToQueue(createIncomingTextMessage(1, msg2));
   addMessageToQueue(createIncomingTextMessage(0, msg1));
   addMessageToQueue(createUserSelectionMessage("1"));
   addMessageToQueue(createExternalUserInfoResponseMessage(1, "1"));

   {
      InSequence s;
      EXPECT_CALL(*userOutputMock, clearOutput());
      EXPECT_CALL(*userOutputMock, print(EndsWith(msg2)));
   }
   out.run();
}

}
