#include <TimerManager.hpp>
#include <iostream>
#include <algorithm>
#include <utility>
#include "InternalMessageSender.hpp"

namespace framework
{

TimerManager::TimerManager(std::shared_ptr<InternalMessageSender> internalMessageSender)
    : internalMessageSender(internalMessageSender),
      id(0)
{
}

int TimerManager::startTimer(int miliseconds)
{
    std::lock_guard<std::mutex> lock(mutex);
    std::chrono::milliseconds timeout{miliseconds};
    auto timeToWakeUp = std::chrono::system_clock::now() + timeout;
    int timerId = ++id;
    scheduledTimers.insert(std::make_pair(timeToWakeUp, timerId));
    conditional.notify_one();
    return timerId++;
}

void TimerManager::stopTimer(int timerId)
{
    std::lock_guard<std::mutex> lock(mutex);

    auto it = std::find_if(scheduledTimers.begin(), scheduledTimers.end(), [=] (std::pair<const Time,int>& pair){return pair.second == timerId;});

    if (it != scheduledTimers.end())
    {
        scheduledTimers.erase(it);
    }

    conditional.notify_one();
}

void TimerManager::run()
{
    running = true;
    while(running)
    {
        std::unique_lock<std::mutex> lock(mutex);
        triggerExpiredTimers();
        conditional.wait_until(lock,getTimeToWakeUp());
        std::cout << "Timer manager woke up" << std::endl;
    }
}

void TimerManager::stop()
{
    std::lock_guard<std::mutex> lock(mutex);
    running = false;
    conditional.notify_one();
}

void TimerManager::triggerExpiredTimers()
{
    auto time = std::chrono::system_clock::now();
    for (auto it = scheduledTimers.begin(); it != scheduledTimers.end();)
    {
        if (it->first < time)
        {
            std::cout << "Timer " << it->second << " expired" << std::endl;
            internalMessageSender->sendTimerExpiredMessage(it->second);
            scheduledTimers.erase(it++);
        }
        else
        {
            break;
        }
    }
}

TimerManager::Time TimerManager::getTimeToWakeUp()
{
    if (not scheduledTimers.empty())
    {
        return scheduledTimers.begin()->first;
    }
    return std::chrono::system_clock::now() + std::chrono::seconds(100);
}

}
