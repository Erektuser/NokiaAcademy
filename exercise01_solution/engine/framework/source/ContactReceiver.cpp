#include "ContactReceiver.hpp"
#include "Utilities.hpp"
#include "Identity.hpp"
#include <iostream>

namespace framework
{

bool isLoopback(int address)
{
    return address == 16777343;
}

ContactReceiver::ContactReceiver(std::string &meetingAddress,
                                 int meetingPort,
                                 int broadcastPort,
                                 int communicationPort,
                                 std::shared_ptr<MessageSender> sender,
                                 std::shared_ptr<IUserOutput> userOutput)
: sender(sender),
  userOutput(userOutput),
  input(broadcastPort, nullptr),
  meetingRoom(getHostAddress(meetingAddress.data()), meetingPort),
  loopback(broadcastPort),
  greetings(),
  running(false)
{
    greetings.indentity = getMyIdentity();
    greetings.broadcastPort = broadcastPort;
    greetings.communicationPort = communicationPort;
    input.connect();
    input.setTimeout(1);
}

void ContactReceiver::run()
{
    running = true;
    bool sentGreetings = true;
    meetingRoom.send(sizeof(greetings), reinterpret_cast<const char*>(&greetings));
    std::string connectingString = "Trying to connect to server";
    userOutput->setClearStatus(connectingString);

    while(running)
    {
        int address{};
        std::unique_ptr<const char> msg {input.receive(address)};
        if (!running)
        {
            return;
        }
        if (*msg == 0)
        {
            if (sentGreetings)
            {
                std::string error = "Failed to connect to a server";
                userOutput->setErrorStatus(error);
                input.setTimeout(1);
            }
            meetingRoom.send(sizeof(greetings), reinterpret_cast<const char*>(&greetings));
            sentGreetings = true;
        }
        else
        {
            sentGreetings = false;
            std::string success = "Connected to a server";
            userOutput->setClearStatus(success);
            input.setTimeout(30);
            const IncommingGreetings& igreetings = reinterpret_cast<const IncommingGreetings&>(*(msg.get()));
            if (igreetings.greetings.indentity != getMyIdentity())
            {
                if (not isLoopback(igreetings.greetings.address))
                {
                    address = igreetings.greetings.address;
                }
                sender->addRecipient(igreetings.greetings.indentity, address, igreetings.greetings.communicationPort);
            }
        }
    }
}

void ContactReceiver::stop()
{
    running = false;
    loopback.send(sizeof(greetings), reinterpret_cast<const char*>(&greetings));
}

}
