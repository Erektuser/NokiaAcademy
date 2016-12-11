#pragma once

#include <memory>
namespace framework
{
    class IUserOutput;
    class IService;
    class IServiceRunner;
    class ILogger;
    class ITimerManager;
    class IMessageReceiver;
    class IMessageSender;
};

namespace engine
{
    std::shared_ptr<framework::IUserOutput> createMainWindow();
    std::shared_ptr<framework::IService> createIncomingConnection(int port);
    std::shared_ptr<framework::IService> createMeetingRoom(int port);
    std::shared_ptr<framework::IService> createContactReceiver(std::string &address, int meetingPort, int broadcastPort, int communicationPort);
    std::shared_ptr<framework::IService> createTimerManagerService();
    std::shared_ptr<framework::IServiceRunner> createServiceRunner();
    std::shared_ptr<framework::ILogger> getLogger();
    std::shared_ptr<framework::ITimerManager> createTimerManager();
    std::shared_ptr<framework::IMessageReceiver> getInternalQueue();
    std::shared_ptr<framework::IMessageSender> getMessageSender();
    std::shared_ptr<framework::IMessageSender> getMessageWithIdentitySender();

    void createApplication(int argc, char* argv[], const std::string &id);
    void startApplication();
};
