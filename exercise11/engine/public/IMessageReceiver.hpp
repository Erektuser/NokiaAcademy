#pragma once

namespace framework
{

class IMessageReceiver
{
public:
    virtual ~IMessageReceiver() {}

    virtual const char * receive() = 0;
};

}
