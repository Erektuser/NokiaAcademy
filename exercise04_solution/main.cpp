#include <memory>
#include <string>
#include <Engine.hpp>
#include "Identity.hpp"
#include <IServiceRunner.hpp>
#include <MainProgram.hpp>

std::string appId(int port)
{
    return "communicator.nokia.a"+ std::to_string(port) + "a";
}

namespace solution
{
std::shared_ptr<framework::IService> createMainProgram()
{
    std::shared_ptr<solution::MainProgram> mainProgram(new solution::MainProgram(engine::getInternalQueue(),
                engine::getMessageWithIdentitySender(),
                engine::createMainWindow(),
                engine::createTimerManager()));

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
