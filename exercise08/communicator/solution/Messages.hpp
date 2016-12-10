#pragma once

namespace solution
{

enum class MsgType : uint8_t
{
    Internal = 1,
    External = 2
};

enum class MsgId : uint16_t
{
    Exit = 1,
    Text = 2,
    UserSelected = 5,
    Timer = 6
};

struct Timer
{
    uint32_t    timerId;
} __attribute__((__packed__));

struct UserInput
{
    uint16_t    size;
    char        data[0];
} __attribute__((__packed__));

union MsgData
{
    Timer     msgTimer;
    UserInput msgUserInput;
};

struct Internal
{
    MsgId   msgId;
    MsgData msgData;
} __attribute__((__packed__));

struct External
{
    uint64_t    identity;
    MsgId       msgId;
    uint16_t    size;
    char        data[0];
}  __attribute__((__packed__));

union Body
{
    Internal internal;
    External external;
};

struct Message
{
    MsgType type;
    Body    body;
} __attribute__((__packed__));

}
