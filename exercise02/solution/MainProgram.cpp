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

const char * MainProgram::receive()
{
    return receiver->receive();
}

void MainProgram::run()
{
    while(true)
    {
        const char * message = receive();
        const short * innerMessage = (const short*)(&message[1]);

        if (message[0] == 1)
        {
            if (innerMessage[0] == 1)
            {
                return;
            }
        }

        // Write code to handle user input and send message to first user from the list
    }
}
}
