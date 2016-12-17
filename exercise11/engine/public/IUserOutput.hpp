#pragma once
#include <string>

namespace framework
{
class IUserOutput
{
public:
    virtual void print(const std::string& message) = 0;
    virtual void addRecipient(const std::string& message) = 0;
    virtual void setRecipientStatus(const std::string& receipent, char status) = 0;
    virtual void setClearStatus(const std::string& status) = 0;
    virtual void setErrorStatus(const std::string& status) = 0;
    virtual void clearOutput() = 0;

    virtual ~IUserOutput(){}
};
}
