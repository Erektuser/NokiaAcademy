#include "MessageTypes.hpp"
#include <algorithm>
#include <tuple>

namespace framework
{
Message createExitMessage()
{
    Message result {};
    result.messageType = static_cast<short>(MessageId::EXIT);
    return result;
}

Message createTextMessage(std::string& text)
{
    Message result {};
    result.messageType = static_cast<short>(MessageId::TEXT);
    int size = std::min(static_cast<int>(text.size()), MAX_TEXT_LENGHT);
    std::copy(text.begin(), text.begin() + size, result.data.text.data);
    result.data.text.length = static_cast<short>(size);
    return result;
}

Message createTimerMesssage(int timerId)
{
    Message result {};
    result.messageType = static_cast<short>(MessageId::TIMER_EXPIRED);
    result.data.timer.timerId = timerId;
    return result;
}

char* toBytes(Message& msg)
{
    return reinterpret_cast<char*>(&msg);
}

bool CompareGreetings::operator()(const Greetings &a, const Greetings &b)
{
    return std::make_tuple(a.address, a.broadcastPort, a.communicationPort) <
           std::make_tuple(b.address, b.broadcastPort, b.communicationPort);
}

bool operator!=(const Greetings &a, const Greetings &b)
{
    return std::make_tuple(a.address, a.broadcastPort, a.communicationPort) !=
           std::make_tuple(b.address, b.broadcastPort, b.communicationPort);
}

}
