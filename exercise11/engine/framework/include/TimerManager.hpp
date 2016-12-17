#pragma once

#include "ITimerManager.hpp"
#include "IService.hpp"
#include <memory>
#include <map>
#include <chrono>
#include <mutex>
#include <condition_variable>


namespace framework
{
struct InternalMessageSender;

class TimerManager : public ITimerManager, public IService
{
public:
    TimerManager(std::shared_ptr<InternalMessageSender> internalMessageSender);
    int startTimer(int miliseconds) override;
    void stopTimer(int timerId) override;
    void run() override;
    void stop() override;
private:
    using Time = std::chrono::time_point<std::chrono::system_clock>;
    void triggerExpiredTimers();
    Time getTimeToWakeUp();

    std::shared_ptr<InternalMessageSender> internalMessageSender;
    std::multimap<Time, int> scheduledTimers;
    std::mutex mutex;
    std::condition_variable conditional;
    bool running;
    unsigned int id;
};
}
