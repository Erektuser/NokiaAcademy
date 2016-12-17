#include "BasicMainProgramTestSuite.hpp"

namespace tests
{
namespace
{
const framework::Identity USER_ID_1 = 0;
const framework::Identity USER_ID_2 = 1;
const std::string USER_NAME = "SomeUser";
}

struct AcceptanceTests_UserNameResolution : public BasicMainProgramTestSuite
{
};

TEST_F(AcceptanceTests_UserNameResolution, storeUserNameOnlyOnce)
{
    addMessageToQueue(createExternalUserInfoResponseMessage(USER_ID_1, USER_NAME));
    addMessageToQueue(createExternalUserInfoResponseMessage(USER_ID_1, USER_NAME));
    EXPECT_CALL(*userOutputMock, addRecipient(StrEq(USER_NAME))).Times(1);
    out.run();
}

TEST_F(AcceptanceTests_UserNameResolution, handleUserInfoRequest)
{
    EXPECT_CALL(*senderMock, sendTo(USER_ID_1, _, _));
    addMessageToQueue(createExternalUserInfoRequestMessage(USER_ID_1));
    out.run();
}

TEST_F(AcceptanceTests_UserNameResolution, handleTimer)
{
    const std::set<framework::Identity> identities{USER_ID_1, USER_ID_2};

    EXPECT_CALL(*senderMock, getAddresses()).WillRepeatedly(ReturnRef(identities));
    EXPECT_CALL(*timerManagerMock, startTimer(1000)).Times(2);

    EXPECT_CALL(*senderMock, sendTo(USER_ID_1, _, _));
    EXPECT_CALL(*senderMock, sendTo(USER_ID_2, _, _));

    addTimerExpirationMessage(1000);
    out.run();
}

TEST_F(AcceptanceTests_UserNameResolution, handleUserSelectionMessage)
{
    const std::string msg1 = "Msg1";
    const std::string msg2 = "Msg2";
    const std::string userName = "TestUserName";

    addMessageToQueue(createUserSelectionMessage(userName));
    addMessageToQueue(createExternalUserInfoResponseMessage(ULONG_MAX, userName));
    addMessageToQueue(createIncomingTextMessage(ULONG_MAX, msg2));
    addMessageToQueue(createIncomingTextMessage(ULONG_MAX-1, msg1));

    {
       InSequence s;
       EXPECT_CALL(*userOutputMock, setRecipientStatus(_, '!')).Times(AtLeast(0));
       EXPECT_CALL(*userOutputMock, print(EndsWith(msg1)));
       EXPECT_CALL(*userOutputMock, setRecipientStatus(_, '!')).Times(AtLeast(0));
       EXPECT_CALL(*userOutputMock, addRecipient(StrEq(userName)));
       EXPECT_CALL(*userOutputMock, clearOutput());
       EXPECT_CALL(*userOutputMock, print(EndsWith(msg2)));
       EXPECT_CALL(*userOutputMock, setRecipientStatus(StrEq(userName), ' '));
    }
    out.run();
}

}
