#pragma once

namespace framework
{
class IOutgoingConnection
{
public:
    virtual void send (const std::string& message) = 0;
    virtual void send(int size, const char *) = 0;

    virtual ~IOutgoingConnection(){}
};
}
