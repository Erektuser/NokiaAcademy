#include "MainProgram.hpp"

namespace solution
{
const int TIMER_DURATION = 1000;

MainProgram::MainProgram(const std::shared_ptr<framework::IMessageReceiver> & receiver,
                         const std::shared_ptr<framework::IMessageSender> & sender,
                         const std::shared_ptr<framework::IUserOutput> & userOutput,
                         const std::shared_ptr<framework::ITimerManager> & timerManager)
    :   receiver(receiver),
        messageSender(sender),
        userOutput(userOutput),
        timerManager(timerManager)
{}

std::unique_ptr<const Message> MainProgram::receive()
{
    return std::unique_ptr<const Message>(reinterpret_cast<const Message *>(receiver->receive()));
}

void MainProgram::print(const std::string & message)
{
    userOutput->print(message);
}

void MainProgram::send(int size, const char * message)
{
    for(const auto& user : messageSender->getAddresses())
    {
        messageSender->sendTo(user, size, message);
    }
}

void MainProgram::run()
{
    while(true)
    {
        auto&& msg = receive();
        if(msg->type == MsgType::Internal)
        {
            if(msg->body.internal.msgId == MsgId::Exit)
            {
                return;
            }
            if (msg->body.internal.msgId == MsgId::Text)
            {
                const std::size_t size = msg->body.internal.size;
                const std::string text {msg->body.internal.data, size};
                print( "[Me] " + text);
                send(size + 4, reinterpret_cast<const char *>(msg.get()) + 1);
            }
        }
        if(msg->type == MsgType::External)
        {
            if(msg->body.external.msgId == MsgId::Text)
            {
                const std::size_t size = msg->body.external.size;
                const std::string text {msg->body.external.data, size};
                print("[unknown] " + text);
            }
        }
    }
}
}
