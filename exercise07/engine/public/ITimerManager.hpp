#pragma once

namespace framework
{

class ITimerManager
{
public:
    virtual int startTimer(int miliseconds) = 0;
    virtual void stopTimer(int timerId) = 0;

    virtual ~ITimerManager(){}
};
}
