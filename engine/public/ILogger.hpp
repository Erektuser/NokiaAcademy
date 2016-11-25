#pragma once

#include <string>

namespace framework
{

class ILogger
{
public:
    virtual void logError(const std::string&) = 0;
    virtual void logWarrning(const std::string&) = 0;
    virtual void logInfo(const std::string&) = 0;

    virtual ~ILogger(){}
};
}
