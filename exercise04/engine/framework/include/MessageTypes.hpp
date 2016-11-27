#pragma once

#include <string>
#include "Identity.hpp"

namespace framework
{

const int MAX_TEXT_LENGHT = 1000;

enum class MessageType : char
{
    INTERNAL = 1,
    EXTERNAL = 2
};

enum class MessageId : short
{
    EXIT = 1,
    TEXT = 2,
    USER_INFO_RESPONSE = 3,
    USER_INFO_REQUEST = 4,
    RECIPIENT_SELECTED = 5,
    TIMER_EXPIRED = 6
};

struct UserInfoResponse
{
    short length;
    char data[1];
} __attribute__ ((__packed__));

struct TextMessage
{
    short length;
    char data[MAX_TEXT_LENGHT];
} __attribute__ ((__packed__));

struct TimerMessage
{
    int timerId;
} __attribute__ ((__packed__));

union Data
{
    TextMessage text;
    UserInfoResponse userInfoResponse;
    TimerMessage timer;
};

struct Message
{
    short messageType;
    Data data;
} __attribute__ ((__packed__));

struct OutgoingMessage
{
    Identity identity;
    Message message;
} __attribute__ ((__packed__));

Message createExitMessage();

Message createTextMessage(std::string& text);

Message createTimerMesssage(int timerId);

char* toBytes(Message& msg);

struct Greetings
{
    Identity indentity;
    int address;
    int broadcastPort;
    int communicationPort;
} __attribute__ ((__packed__));

struct IncommingGreetings
{
    char type;
    Greetings greetings;
}  __attribute__ ((__packed__));

struct CompareGreetings
{
bool operator()(const Greetings &a, const Greetings &b);
};

bool operator!=(const Greetings &a, const Greetings &b);
}
