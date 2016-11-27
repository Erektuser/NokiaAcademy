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
    Text = 2
};

struct Internal
{
    MsgId msgId;
    uint16_t size;
    char data[0];
} __attribute__((__packed__));

struct External
{
    uint64_t identity;
    MsgId msgId;
    uint16_t size;
    char data[0];
} __attribute__((__packed__));

union Body
{
    Internal internal;
    External external;
};

struct Message
{
    MsgType type;
    Body body;
} __attribute__((__packed__));

}
