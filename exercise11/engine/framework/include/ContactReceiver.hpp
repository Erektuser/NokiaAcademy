#pragma once

#include <IService.hpp>
#include "MessageSender.hpp"
#include "IncomingConnection.hpp"
#include "MessageTypes.hpp"
#include <IUserOutput.hpp>
#include <memory>

namespace framework
{
class ContactReceiver : public IService
{
public:
    ContactReceiver(std::string& meetingAddress,
                    int meetingPort,
                    int broadcastPort,
                    int communicationPort,
                    std::shared_ptr<MessageSender> sender,
                    std::shared_ptr<IUserOutput> userOutput);
    void run() override;
    void stop() override;
private:
    std::shared_ptr<MessageSender> sender;
    std::shared_ptr<IUserOutput> userOutput;
    IncomingConnection input;
    OutgoingConnection meetingRoom;
    OutgoingConnection loopback;
    Greetings greetings;
    bool running;
};
}
