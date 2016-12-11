#include "BasicMainProgramTestSuite.hpp"
#include "UserHistory.hpp"
#include <string>
#include <memory>

namespace tests
{

struct AcceptanceTests_UserHistory : public Test
{
    const std::string msg0 = "msg0";
    const std::string msg1 = "msg1";
    const std::string msg2 = "msg2";
    std::shared_ptr<solution::IUserHistory> userHistory = std::make_shared<solution::UserHistory>();
};

TEST_F(AcceptanceTests_UserHistory, checkCountOfAddedMessages)
{
    userHistory->addToHistory(msg0);
    userHistory->addToHistory(msg1);
    userHistory->addToHistory(msg2);
    ASSERT_EQ(userHistory->getHistoryCount(),3);
}

TEST_F(AcceptanceTests_UserHistory, checkContentofUserHistory)
{
    userHistory->addToHistory(msg0);
    userHistory->addToHistory(msg1);
    userHistory->addToHistory(msg2);

    auto history = userHistory->getHistory();
    ASSERT_EQ(history[0], msg0);
    ASSERT_EQ(history[1], msg1);
    ASSERT_EQ(history[2], msg2);
}

}
