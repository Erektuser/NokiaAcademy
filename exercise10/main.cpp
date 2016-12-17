#include <memory>
#include <string>
#include <Engine.hpp>
#include "Identity.hpp"
#include <IServiceRunner.hpp>
#include <MainProgram.hpp>
#include <Commands.hpp>
#include <DataHolder.hpp>

std::string appId(int port)
{
    return "communicator.nokia.a"+ std::to_string(port) + "a";
}

namespace solution
{
std::shared_ptr<framework::IService> createMainProgram()
{
    std::shared_ptr<solution::DataHolder> holder(std::make_shared<solution::DataHolder>());
    std::shared_ptr<framework::IMessageReceiver> receiver(engine::getInternalQueue());
    std::shared_ptr<framework::IMessageSender> sender(engine::getMessageWithIdentitySender());
    std::shared_ptr<framework::IUserOutput> userOutput(engine::createMainWindow());
    std::shared_ptr<framework::ITimerManager> timerManager(engine::createTimerManager());

    CommandsPtr commands = solution::createCommands(
            holder,
            receiver,
            sender,
            userOutput,
            timerManager);
    std::shared_ptr<solution::MainProgram> mainProgram(new solution::MainProgram(
            std::move(commands),
            holder,
            receiver,
            sender,
            userOutput,
            timerManager));

    return mainProgram;
}
}

int main(int argc, char* argv[])
{
    int communicationPort = 8100;
    int meetingPort = 8102;
    std::string meetingAddress = "localhost";

    if (argc > 1)
    {
        communicationPort = std::stoi(argv[1]);
    }
    argc = 1;

    framework::initializeIdentity(communicationPort);

    int broadcastPort = communicationPort + 1;
    int localMeetingPort = communicationPort + 2;

    engine::createApplication(argc, argv, appId(communicationPort));

    auto serviceRunner = engine::createServiceRunner();
    serviceRunner->startService(engine::createIncomingConnection(communicationPort));
    serviceRunner->startService(solution::createMainProgram());
    serviceRunner->startService(engine::createMeetingRoom(localMeetingPort));
    serviceRunner->startService(engine::createContactReceiver(meetingAddress, meetingPort, broadcastPort, communicationPort));
    serviceRunner->startService(engine::createTimerManagerService());
    
    engine::startApplication();
}
