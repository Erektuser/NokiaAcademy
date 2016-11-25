#include "InternalMessageSender.hpp"
#include "IOutgoingConnection.hpp"
#include "MessageTypes.hpp"
#include "InternalQueue.hpp"

namespace framework
{

void InternalMessageSender::sendExitMessage()
{
    Message msg = createExitMessage();
    queue->copyAndSend(sizeof(msg), toBytes(msg));
}

void InternalMessageSender::sendTextMessage(std::string& text)
{
    Message msg = createTextMessage(text);
    queue->copyAndSend(sizeof(msg), toBytes(msg));
}


void InternalMessageSender::sendSetRecipient(std::string& name)
{
    Message msg = createTextMessage(name);
    msg.messageType = static_cast<char>(MessageId::RECIPIENT_SELECTED);
    queue->copyAndSend(sizeof(msg), toBytes(msg));
}

void InternalMessageSender::sendTimerExpiredMessage(int timerId)
{
    Message msg = createTimerMesssage(timerId);
    queue->copyAndSend(sizeof(msg), toBytes(msg));
}

}
