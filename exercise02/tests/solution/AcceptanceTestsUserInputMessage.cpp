#include "BasicMainProgramTestSuite.hpp"
#include "MessageFactoryFunctions.hpp"
#include <string>

namespace tests
{

struct AcceptanceTests_UserInputMessage : public BasicMainProgramTestSuite
{
    std::set<framework::Identity> identities = { 1 };

    void sendUserTypedMessage(const std::string& message)
    {
        char *msg = new char[1000];
        Message::Body::Internal *hdr = reinterpret_cast<Message::Body::Internal*>(msg);
        hdr->size = message.size();
        hdr->msgId = MsgId::Text;
        std::copy(message.data(), message.data()+message.size(), hdr->data);

        EXPECT_CALL(*senderMock, getAddresses()).WillRepeatedly(ReturnRef(identities));

        std::vector<char> vec(msg, msg + message.length()+4);
        EXPECT_CALL(*senderMock, sendTo(framework::Identity(1), ElementsAreArray(vec)));

        addMessageToQueue(createUserTypedTextMessage(message));
    }
    
    void printTypedMessage(const std::string& message)
    {
        std::string expected = "[Me] " + message;
        EXPECT_CALL(*userOutputMock, print(StrEq(expected)));
        ON_CALL(*senderMock, getAddresses()).WillByDefault(ReturnRef(identities));
        addMessageToQueue(createUserTypedTextMessage(message));
    }

};


TEST_F(AcceptanceTests_UserInputMessage, printBasicUserInputMessage)
{
    printTypedMessage("Hello world!");
    out.run();
}

TEST_F(AcceptanceTests_UserInputMessage, printEmptyUserInputMessage)
{
    printTypedMessage("");
    out.run();
}

TEST_F(AcceptanceTests_UserInputMessage, printExtendedUserInputMessage)
{
    printTypedMessage("Last one, a bit longer and with some extra chars like !@#$$%^&*()_+=-``''\n\n");
    out.run();
}


TEST_F(AcceptanceTests_UserInputMessage, sendBasicUserInputMessage)
{
    sendUserTypedMessage("Hello World!");
    out.run();
}

TEST_F(AcceptanceTests_UserInputMessage, sendExtendUserInputMessage)
{
    sendUserTypedMessage("Last one, a bit longer and with some extra chars like !@#$$%^&*()_+=-``''\n\n");
    out.run();
}

TEST_F(AcceptanceTests_UserInputMessage, sendEmptyUserInputMessage)
{
    sendUserTypedMessage("");
    out.run();
}

}
