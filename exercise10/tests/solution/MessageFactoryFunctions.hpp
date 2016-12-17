#pragma once

#include <Identity.hpp>
#include <string>

namespace tests
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

struct Message
{
    MsgType type;

    union Body
    {
        struct Internal
        {
            MsgId       msgId;
            uint16_t    size;
            char        data[0];
        } internal __attribute__((__packed__));

        struct External
        {
            uint64_t    identity;
            MsgId       msgId;
            uint16_t    size;
            char        data[0];
        } external __attribute__((__packed__));
    } body;
} __attribute__((__packed__));

const char * createExitMessage();
const char * createTimerExpirationMessage(unsigned int id);
const char * createUserSelectionMessage(const std::string & text);
const char * createIncomingTextMessage(framework::Identity identity, const std::string & text);

const char * createUserTypedTextMessage(const std::string &text);

}
