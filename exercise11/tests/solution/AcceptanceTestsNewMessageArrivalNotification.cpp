#include "BasicMainProgramTestSuite.hpp"
#include "MessageFactoryFunctions.hpp"
#include <string>

namespace tests
{

struct AcceptanceTests_NewMessageArrivalNotification : public BasicMainProgramTestSuite
{
    void addIncomingTextMessage(const std::string& message)
    {
        std::string expected = "[unknown] " + message;
        EXPECT_CALL(*userOutputMock, print(StrEq(expected)));
        addMessageToQueue(createIncomingTextMessage(0,message));
    }
};

TEST_F(AcceptanceTests_NewMessageArrivalNotification, clearRecipientStatusUponUserSelection)
{
    static const std::string id{"1"};
    addMessageToQueue(createUserSelectionMessage(id));
    addMessageToQueue(createExternalUserInfoResponseMessage(1, "1"));
    EXPECT_CALL(*userOutputMock, setRecipientStatus(id, ' '));
    out.run();
}

TEST_F(AcceptanceTests_NewMessageArrivalNotification, pickUpFirstUserWhenNoUserSelectedAndSetRecipientStatusAnyway)
{
    static const framework::Identity id(0);
    addMessageToQueue(createIncomingTextMessage(id, "Msg1"));
    EXPECT_CALL(*userOutputMock, setRecipientStatus(std::to_string(id), '!'));
    out.run();
}

TEST_F(AcceptanceTests_NewMessageArrivalNotification, setRecipientStatusForNotSelectedUser)
{
    static const std::string id_0{"0"};
    static const std::string id_1{"1"};
    addMessageToQueue(createIncomingTextMessage(std::stoul(id_0), "Msg2"));
    addMessageToQueue(createUserSelectionMessage(id_1));
    addMessageToQueue(createExternalUserInfoResponseMessage(1, "1"));
    addMessageToQueue(createExternalUserInfoResponseMessage(0, "0"));

    EXPECT_CALL(*userOutputMock, setRecipientStatus(id_1, ' '));
    EXPECT_CALL(*userOutputMock, setRecipientStatus(_, '!'));

    out.run();
}

}
