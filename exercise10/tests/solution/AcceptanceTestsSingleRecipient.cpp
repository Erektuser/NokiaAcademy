#include "BasicMainProgramTestSuite.hpp"
#include "MessageFactoryFunctions.hpp"
#include <string>

namespace tests
{

struct AcceptanceTests_SingleRecipient : public BasicMainProgramTestSuite
{
    void SetUp()
    {
        EXPECT_CALL(*senderMock, getAddresses()).Times(0);
    }

    void addIncomingTextMessage(const std::string& message)
    {
        std::string expected = "[unknown] " + message;
        EXPECT_CALL(*userOutputMock, print(StrEq(expected)));
        addMessageToQueue(createIncomingTextMessage(0,message));
    }
};

TEST_F(AcceptanceTests_SingleRecipient, sendMessageToSelectedUserOnly)
{
   static const std::string id{"1"};
   addMessageToQueue(createUserTypedTextMessage("Hello"));
   addMessageToQueue(createUserSelectionMessage(id));
   EXPECT_CALL(*senderMock, sendTo(std::stoll(id), _, _)).Times(1);
   out.run();
}

TEST_F(AcceptanceTests_SingleRecipient, sendMessageToSelectedUserOnlyAfterUserChange)
{
   static const std::string id{"1"};
   static const std::string id2{"2"};
   addMessageToQueue(createUserTypedTextMessage("Hello"));
   addMessageToQueue(createUserSelectionMessage(id2));
   addMessageToQueue(createUserSelectionMessage(id));
   EXPECT_CALL(*senderMock, sendTo(std::stoll(id2), _, _)).Times(1);
   EXPECT_CALL(*senderMock, sendTo(std::stoll(id), _, _)).Times(0);
   out.run();
}

TEST_F(AcceptanceTests_SingleRecipient, noMessageSendWhenNoUserSelected)
{
   addMessageToQueue(createUserTypedTextMessage("Hello"));

   EXPECT_CALL(*senderMock, sendTo(_, _, _)).Times(0);
   EXPECT_CALL(*userOutputMock, print(_)).Times(0);
   out.run();
}

}
