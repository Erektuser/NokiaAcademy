#include <TerminalLogger.hpp>
#include <iostream>

namespace framework
{
void TerminalLogger::logError(const std::string & message)
{
    std::cerr << "Error: " << message << std::endl;
}

void TerminalLogger::logWarrning(const std::string & message)
{
    std::cout << "Warning: " << message << std::endl;
}

void TerminalLogger::logInfo(const std::string & message)
{
    std::cout << "Info: " << message << std::endl;
}
}
