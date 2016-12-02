#pragma once

#include <gmock/gmock.h>
#include <ITimerManager.hpp>

namespace tests
{
struct TimerManagerMock : public framework::ITimerManager
{
    MOCK_METHOD1(startTimer, int (int miliseconds));
    MOCK_METHOD1(stopTimer, void (int timerId));
};
}
