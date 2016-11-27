#pragma once

#include <thread>
#include <vector>
#include <memory>
#include "IService.hpp"
#include <IServiceRunner.hpp>

namespace framework
{
class ServiceRunner : public IServiceRunner
{
public:
    ServiceRunner();
    ~ServiceRunner() override;
    void startService(const std::shared_ptr<IService> &service) override;
    void stopServices() override;
private:
    std::vector<std::shared_ptr<IService>> services;
    std::vector<std::shared_ptr<std::thread>> threads;
};
}
