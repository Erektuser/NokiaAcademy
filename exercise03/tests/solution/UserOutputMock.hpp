#pragma once

#include <gmock/gmock.h>
#include <IUserOutput.hpp>

namespace tests
{
struct UserOutputMock: public framework::IUserOutput
{
    MOCK_METHOD1(print, void(const std::string& message));
    MOCK_METHOD1(addRecipient, void (const std::string& message));
    MOCK_METHOD2(setRecipientStatus, void (const std::string& receipent, char status));
    MOCK_METHOD1(setClearStatus, void (const std::string& status));
    MOCK_METHOD1(setErrorStatus, void (const std::string& status));
    MOCK_METHOD0(clearOutput, void ());
};
}
