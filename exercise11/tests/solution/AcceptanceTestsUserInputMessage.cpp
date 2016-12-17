#include "BasicMainProgramTestSuite.hpp"
#include <string>

namespace tests
{
namespace
{
const framework::Identity USER_ID_1 = 1;
const std::string USER_NAME = "SomeUser";
}

struct AcceptanceTests_UserInputMessage : public BasicMainProgramTestSuite
{
    std::set<framework::Identity> identities = { 1 };

    void userTypedMessage(const std::string & message)
    {
        char *msg = new char[1000];
        Message::Body::Internal *hdr = reinterpret_cast<Message::Body::Internal *>(msg);
        hdr->size = message.size();
        hdr->msgId = MsgId::Text;
        std::copy(message.data(), message.data()+message.size(), hdr->data);

        std::string expected = "[Me] " + message;
        EXPECT_CALL(*userOutputMock, print(StrEq(expected)));
        EXPECT_CALL(*senderMock, getAddresses()).WillRepeatedly(ReturnRef(identities));

        EXPECT_CALL(*senderMock, sendTo(framework::Identity(1), message.size()+4, _)).Times(1);

        addMessageToQueue(createUserTypedTextMessage(message));
    }
};

TEST_F(AcceptanceTests_UserInputMessage, handleBasicUserInputMessage)
{
    userTypedMessage("Hello World!");
    addMessageToQueue(createUserSelectionMessage(USER_NAME));
    addMessageToQueue(createExternalUserInfoResponseMessage(USER_ID_1, USER_NAME));

    out.run();
}

TEST_F(AcceptanceTests_UserInputMessage, handleExtendUserInputMessage)
{
    userTypedMessage("");
    userTypedMessage("Last one, a bit longer and with some extra chars like !@#$$%^&*()_+=-``''\n\n");
    addMessageToQueue(createUserSelectionMessage(USER_NAME));
    addMessageToQueue(createExternalUserInfoResponseMessage(USER_ID_1, USER_NAME));

    out.run();
}

}
