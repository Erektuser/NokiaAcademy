#include "MainProgram.hpp"
#include <string>
#include <iostream>

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

void MainProgram::run()
{
    const char*  msg = receiver->receive();
    // Write main loop with handling exit message
    // Run test. Verify that program runs and closes properly
}
}
