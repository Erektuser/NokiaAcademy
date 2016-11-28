#pragma once

#include "ILogger.hpp"

namespace framework
{

class TerminalLogger : public ILogger
{
public:
    virtual void logError(const std::string &) override;
    virtual void logWarrning(const std::string &) override;
    virtual void logInfo(const std::string &) override;
};
}
