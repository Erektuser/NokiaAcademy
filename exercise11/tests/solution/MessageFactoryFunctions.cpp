#include "MessageFactoryFunctions.hpp"
#include <algorithm>
#include <string.h>
#include <iostream>
namespace tests
{

namespace
{
    struct IncomingTextMessage
    {
        IncomingTextMessage(const std::string& text, framework::Identity identity)
            :messageType(2),
             identity(identity),
             messageId(2),
             length(text.size())
        {
            std::copy(text.data(), text.data() + text.size(), data);
        }
        char messageType;
        framework::Identity identity;
        short messageId;
        short length;
        char data[1024];
    } __attribute__ ((__packed__));


    struct UserSelectionMessage
    {
        UserSelectionMessage(const std::string& text)
            :messageType(1),
             messageId(5),
             length(text.size())
        {
            std::copy(text.data(), text.data() + text.size(), data);
        }
        char messageType;
        short messageId;
        short length;
        char data[1024];
    } __attribute__ ((__packed__));

    struct TimerExpirationMessage
    {
        TimerExpirationMessage(unsigned int id)
            :messageType(1),
             messageId(6),
             timerId(id)
        {

        }
        char messageType;
        short messageId;
        uint32_t timerId;

    } __attribute__ ((__packed__));
}


const char * createExitMessage()
{
    char * buffer = new char[5]();
    buffer[0] = 1;
    buffer[1] = 1;
    return buffer;
}

const char * createTimerExpirationMessage(unsigned int id)
{
    TimerExpirationMessage textMessage{id} ;
    char * textMessageInChars = reinterpret_cast<char *>(&textMessage);
    char * buffer = new char[sizeof(IncomingTextMessage)]();
    std::copy(textMessageInChars, textMessageInChars + sizeof(textMessage), buffer);
    return buffer;

}

const char * createUserSelectionMessage( const std::string &text)
{
     UserSelectionMessage textMessage{text};
     char * textMessageInChars = reinterpret_cast<char *>(&textMessage);
     char * buffer = new char[sizeof(IncomingTextMessage)]();
     std::copy(textMessageInChars, textMessageInChars + sizeof(textMessage), buffer);
     return buffer;

}

const char * createIncomingTextMessage(framework::Identity identity, const std::string &text)
{
    IncomingTextMessage textMessage{text, identity};
    char * textMessageInChars = reinterpret_cast<char *>(&textMessage);
    char * buffer = new char[sizeof(IncomingTextMessage)]();
    std::copy(textMessageInChars, textMessageInChars + sizeof(textMessage), buffer);
    return buffer;
}

const char * createUserTypedTextMessage(const std::string &text)
{
    char *msg = new char[sizeof(Message) + text.length() + 5];
    Message *hdr = reinterpret_cast<Message*>(msg);
    hdr->type = MsgType::Internal;
    hdr->body.internal.msgId = MsgId::Text;
    hdr->body.internal.size = text.length();
    const char *data = text.c_str();
    std::copy(data, data+text.length(), hdr->body.internal.data);
    return msg;
}

const char * createExternalUserInfoRequestMessage(framework::Identity identity)
{
    char *msg = new char[1000];
    Message *hdr = reinterpret_cast<Message*>(msg);
    hdr->type = MsgType::External;
    hdr->body.external.identity = identity;
    hdr->body.external.msgId = MsgId::UserInfoReq;
    return msg;
}

const char * createExternalUserInfoResponseMessage(framework::Identity identity, const std::string & name)
{
    char *msg = new char[1000];
    Message *hdr = reinterpret_cast<Message*>(msg);
    hdr->type = MsgType::External;
    hdr->body.external.identity = identity;
    hdr->body.external.msgId = MsgId::UserInfoResp;
    hdr->body.external.size = name.size();
    std::copy(name.data(), name.data() + name.size(), hdr->body.external.data);
    return msg;
}

}
