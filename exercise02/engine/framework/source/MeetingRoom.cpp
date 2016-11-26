#include "MeetingRoom.hpp"
#include <chrono>
#include <thread>

namespace framework
{

MeetingRoom::MeetingRoom(int port)
    : broadcast(),
      input(port, nullptr),
      running(false),
      port(port)
{

}

void MeetingRoom::run()
{
    running = true;
    input.connect();
    while (running)
    {
        int address {};
        std::unique_ptr<const char> msg(input.receive(address));
        const IncommingGreetings &greeting = *(reinterpret_cast<const IncommingGreetings*>(msg.get()));
        if (greeting.greetings.address != 0xFFFFFFFF)
        {
            addGreetings(address, greeting.greetings);
            broadcastGreetings();
        }
    }
}

void MeetingRoom::addGreetings(int address, Greetings greeting)
{
    greeting.address = address;
    greetings.insert(greeting);
    broadcast.addRecipient(greeting.indentity, greeting.address, greeting.broadcastPort);
}

void MeetingRoom::stop()
{
    running = false;
    OutgoingConnection loopback(port);
    Greetings greetings{};
    greetings.address = 0xFFFFFFFF;
    loopback.send(sizeof(Greetings), (const char*)(&greetings));
}

void MeetingRoom::broadcastGreetings()
{
    for(auto& greeting : greetings)
    {
        broadcast.sendToAll(sizeof(greeting), reinterpret_cast<const char*>(&greeting));
    }
}

}
