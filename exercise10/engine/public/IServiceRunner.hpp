#pragma once

#include <memory>

namespace framework
{
class IService;

class IServiceRunner
{
public:
    virtual ~IServiceRunner() {};
    virtual void startService(const std::shared_ptr<IService> &service) = 0;
    virtual void stopServices() = 0;
};

}
