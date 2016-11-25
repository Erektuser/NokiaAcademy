#include "BasicMainProgramTestSuite.hpp"

namespace tests
{

struct AcceptanceTests_ExitMessage : public BasicMainProgramTestSuite
{
};

TEST_F(AcceptanceTests_ExitMessage, handleExitMessage)
{
    out.run();
}

TEST_F(AcceptanceTests_ExitMessage, handleNonExitMessage)
{
    ON_CALL(*receiverMock, receive()).WillByDefault(Return(createNonExitMessage()));
    addMessageToQueue(createNonExitMessage());
    out.run();
}

TEST_F(AcceptanceTests_ExitMessage, handleExitMessageWithWrongEndian)
{
    ON_CALL(*receiverMock, receive()).WillByDefault(Return(createExitMessageWithWrongEndian()));
    addMessageToQueue(createExitMessageWithWrongEndian());
    out.run();
}

}
