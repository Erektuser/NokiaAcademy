#pragma once

#include <IService.hpp>
#include <IUserOutput.hpp>
#include <ILogger.hpp>
#include <IMessageSender.hpp>
#include <IMessageReceiver.hpp>
#include <ITimerManager.hpp>

#include <memory>

namespace solution
{
class MainProgram : public framework::IService
{
    std::shared_ptr<framework::IMessageReceiver> receiver;
    std::shared_ptr<framework::IMessageSender> messageSender;
    std::shared_ptr<framework::IUserOutput> userOutput;
    std::shared_ptr<framework::ITimerManager> timerManager;

public:
    MainProgram(const std::shared_ptr<framework::IMessageReceiver> & receiver,
                const std::shared_ptr<framework::IMessageSender> & sender,
                const std::shared_ptr<framework::IUserOutput> & userOutput,
                const std::shared_ptr<framework::ITimerManager> & timerManager);

    void run() override;
    void stop() override {}
};
}
