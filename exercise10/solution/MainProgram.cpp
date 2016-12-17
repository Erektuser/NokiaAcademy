#include "MainProgram.hpp"
#include <DataHolder.hpp>
#include <iostream>
#include <stdexcept>

namespace solution
{
using namespace framework;
const int TIMER_DURATION = 1000u;

MainProgram::MainProgram(CommandsPtr commands,
                         const std::shared_ptr<solution::DataHolder> & holder,
                         const std::shared_ptr<framework::IMessageReceiver> & receiver,
                         const std::shared_ptr<framework::IMessageSender> & sender,
                         const std::shared_ptr<framework::IUserOutput> & userOutput,
                         const std::shared_ptr<framework::ITimerManager> & timerManager)
    :   internalCommands(std::move(std::get<0>(commands))),
        externalCommands(std::move(std::get<1>(commands))),
        holder(holder),
        receiver(receiver),
        messageSender(sender),
        userOutput(userOutput),
        timerManager(timerManager)
{}

std::unique_ptr<const Message> MainProgram::receive()
{
    return std::unique_ptr<const Message>(reinterpret_cast<const Message *>(receiver->receive()));
}

void MainProgram::processReceivedMessage(const Message & msg)
try
{
    switch(msg.type)
    {
        case MsgType::Internal:
            (*internalCommands)[msg.body.internal.msgId](msg);
            break;
        case MsgType::External:
            (*externalCommands)[msg.body.external.msgId](msg);
            break;
    }
}
catch(const std::exception & e)
{
      std::cerr << "Exception: " << e.what() << std::endl;
}

void MainProgram::run()
{
    int timerId = timerManager->startTimer(TIMER_DURATION);
    while(holder->running)
    {
        auto&& msg = receive();
        processReceivedMessage(*msg);
    }
}

}
