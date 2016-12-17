#pragma once

#include <IService.hpp>
#include <IUserOutput.hpp>
#include <ILogger.hpp>
#include <IMessageSender.hpp>
#include <IMessageReceiver.hpp>
#include <ITimerManager.hpp>
#include <UserHistory.hpp>
#include <Messages.hpp>
#include <Commands.hpp>
#include <memory>
#include <set>
#include <map>

namespace solution
{
struct DataHolder;
extern const int TIMER_DURATION;

class MainProgram : public framework::IService
{
    std::unique_ptr<const Message> receive();
    void processReceivedMessage(const Message & msg);

    std::unique_ptr<ICommands> internalCommands;
    std::unique_ptr<ICommands> externalCommands;
    std::shared_ptr<solution::DataHolder>  holder;
    std::shared_ptr<framework::IMessageReceiver> receiver;
    std::shared_ptr<framework::IMessageSender> messageSender;
    std::shared_ptr<framework::IUserOutput> userOutput;
    std::shared_ptr<framework::ITimerManager> timerManager;
public:
    MainProgram(CommandsPtr commands,
                const std::shared_ptr<solution::DataHolder> & holder,
                const std::shared_ptr<framework::IMessageReceiver> & receiver,
                const std::shared_ptr<framework::IMessageSender> & sender,
                const std::shared_ptr<framework::IUserOutput> & userOutput,
                const std::shared_ptr<framework::ITimerManager> & timerManager);

    void run() override;
    void stop() override {}
};
}
