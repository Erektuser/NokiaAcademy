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

}
