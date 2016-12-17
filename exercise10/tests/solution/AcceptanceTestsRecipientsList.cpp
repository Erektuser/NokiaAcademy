#include "BasicMainProgramTestSuite.hpp"

namespace tests
{
using namespace framework;
using namespace solution;

struct AcceptanceTests_RecipientsList : public BasicMainProgramTestSuite
{
};

TEST_F(AcceptanceTests_RecipientsList, handleTimerExpirationMessage)
{
    const std::set<Identity> identities { 1 };

    addTimerExpirationMessage(TIMER_DURATION);
    EXPECT_CALL(*senderMock, getAddresses()).WillRepeatedly(ReturnRef(identities));
    EXPECT_CALL(*userOutputMock, addRecipient(StrEq("1")));
    EXPECT_CALL(*timerManagerMock, startTimer(TIMER_DURATION)).Times(2);

    out.run();
}

}
