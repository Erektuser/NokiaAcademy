#pragma once
#include <Messages.hpp>
#include <memory>

namespace framework
{
class IMessageReceiver;
class IMessageSender;
class IUserOutput;
class ITimerManager;
}

namespace solution
{
struct DataHolder;

struct ICommand
{
    virtual ~ICommand() {}
    virtual void operator()(const Message & msg) = 0;
};

struct ICommands
{
    virtual ~ICommands() {}
    virtual ICommand & operator[](const MsgId id) = 0;
};

typedef std::tuple<
    std::unique_ptr<ICommands>,
    std::unique_ptr<ICommands>
> CommandsPtr;

CommandsPtr createCommands(
        std::shared_ptr<solution::DataHolder> holder,
        std::shared_ptr<framework::IMessageReceiver> receiver,
        std::shared_ptr<framework::IMessageSender> sender,
        std::shared_ptr<framework::IUserOutput> userOutput,
        std::shared_ptr<framework::ITimerManager> timerManager);

}