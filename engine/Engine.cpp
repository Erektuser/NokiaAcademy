#include "Engine.hpp"
#include "OutgoingConnection.hpp"
#include "IncomingConnection.hpp"
#include "MessageSender.hpp"
#include "MessageWithIdentitySender.hpp"
#include "TerminalLogger.hpp"
#include "InternalQueue.hpp"
#include "InternalMessageSender.hpp"
#include "MeetingRoom.hpp"
#include "ContactReceiver.hpp"
#include "TimerManager.hpp"
#include "ServiceRunner.hpp"
#include "MainWindow.hpp"

namespace engine
{
std::shared_ptr<framework::IServiceRunner> createServiceRunner()
{
    return std::make_shared<framework::ServiceRunner>();
}

std::shared_ptr<framework::InternalQueue> getInternalQueueRaw()
{
    static auto internalQueue = std::make_shared<framework::InternalQueue>();
    return internalQueue;
}

std::shared_ptr<framework::IMessageReceiver> getInternalQueue()
{
    return getInternalQueueRaw();
}

std::shared_ptr<framework::MessageSender> getMessageSenderRaw()
{
    static auto messageSender = std::make_shared<framework::MessageSender>();
    return messageSender;
}

std::shared_ptr<framework::IMessageSender> getMessageSender()
{
    return getMessageSenderRaw();
}

std::shared_ptr<framework::IMessageSender> getMessageWithIdentitySender()
{
    return std::make_shared<framework::MessageWithIdentitySender>(getMessageSenderRaw());
}

std::shared_ptr<framework::IUserOutput> createMainWindow()
{
    static auto internalMessageSender = std::make_shared<framework::InternalMessageSender>(getInternalQueueRaw());
    static auto mainWindow = std::make_shared<gui::MainWindow>(internalMessageSender);
    return mainWindow;
}

std::shared_ptr<framework::IService> createIncomingConnection(int port)
{
    return std::make_shared<framework::IncomingConnection> (port, getInternalQueueRaw());
}

std::shared_ptr<framework::IService> createMeetingRoom(int port)
{
    return std::make_shared<framework::MeetingRoom> (port);
}

std::shared_ptr<framework::IService> createContactReceiver(std::string &address, int meetingPort, int broadcastPort, int communicationPort)
{
    return std::make_shared<framework::ContactReceiver>(address, meetingPort, broadcastPort, communicationPort, getMessageSenderRaw(), createMainWindow());
}

std::shared_ptr<framework::TimerManager> createTimerManagerRaw()
{
    static auto timerManager = std::make_shared<framework::TimerManager>(std::make_shared<framework::InternalMessageSender>(getInternalQueueRaw()));
    return timerManager;
}

std::shared_ptr<framework::IService> createTimerManagerService()
{
    return createTimerManagerRaw();
}

std::shared_ptr<framework::ITimerManager> createTimerManager()
{
    return createTimerManagerRaw();
}

namespace {
    Glib::RefPtr<Gtk::Application> app;
}

void createApplication(int argc, char* argv[], const std::string &id)
{
    if(!Glib::thread_supported()) Glib::thread_init();
    app = Gtk::Application::create(argc, argv, id);
}

void startApplication()
{
    if (!app) return;
    auto window = std::dynamic_pointer_cast<gui::MainWindow>(createMainWindow());
    app->run(*window);
    app.reset();
}

}
