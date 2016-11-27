#include "MainProgram.hpp"

namespace solution
{

MainProgram::MainProgram(const std::shared_ptr<framework::IMessageReceiver> & receiver,
                         const std::shared_ptr<framework::IMessageSender> & sender,
                         const std::shared_ptr<framework::IUserOutput> & userOutput,
                         const std::shared_ptr<framework::ITimerManager> & timerManager)
    :   receiver(receiver),
        messageSender(sender),
        userOutput(userOutput),
        timerManager(timerManager)
{}

std::unique_ptr<const char[]> MainProgram::receive()
{
    return std::unique_ptr<const char[]>(receiver->receive());
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
        auto message = receive();
        const short * innerMessage = (const short*)(&message[1]);
        unsigned short size = 0;
        char buffer[1024] = {};

        if(message[0] == 1)
        {
            if(innerMessage[0] == 1)
            {
                return;
            }
            else if(message[1] == 2)
            {
                size = innerMessage[1];
                for(int i = 0; i < size; ++i)
                {
                    buffer[i] = message[i + 5];
                }
                buffer[size] = 0;
                std::string text(buffer);
                print("[Me] " + text);
                send(size + 4, &message[1]);
            }
        }
        if(message[0] == 2)
        {
            if(innerMessage[4] == 2)
            {
                size = innerMessage[5];
                for (int i = 0; i < size; ++i)
                {
                    buffer[i] = message[i + 13];
                }
                buffer[size] = 0;
                print("[Unknown] " + std::string(buffer));
            }
        }
    }
}
}
