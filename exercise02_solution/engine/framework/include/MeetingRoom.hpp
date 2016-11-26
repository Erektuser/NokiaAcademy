#pragma once

#include "IService.hpp"
#include "MessageSender.hpp"
#include "IncomingConnection.hpp"
#include "MessageTypes.hpp"
#include <set>

namespace framework
{
class MeetingRoom : public IService
{
public:
    MeetingRoom(int port);
    void run() override;
    void stop() override;
private:
    void addGreetings(int address, Greetings greeting);
    void broadcastGreetings();
    MessageSender broadcast;
    IncomingConnection input;
    bool running;
    int port;
    std::set<Greetings, CompareGreetings> greetings;
};
}
