#include "ServiceRunner.hpp"

namespace framework
{

ServiceRunner::ServiceRunner()
{
}

ServiceRunner::~ServiceRunner()
{
    stopServices();
}

void ServiceRunner::startService(const std::shared_ptr<IService> &service)
{
    std::shared_ptr<std::thread> thread(new std::thread([=]{service->run();}));
    threads.push_back(thread);
    services.push_back(service);
}

void ServiceRunner::stopServices()
{
    for (auto& service: services)
    {
        service->stop();
    }
    for (auto& thread: threads)
    {
        thread->join();
    }
    threads.clear();
    services.clear();
}

}
