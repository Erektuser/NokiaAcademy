#pragma once

namespace framework
{
class IService
{
public:
    virtual void run() = 0;
    virtual void stop() = 0;

    virtual ~IService(){}
};
}
