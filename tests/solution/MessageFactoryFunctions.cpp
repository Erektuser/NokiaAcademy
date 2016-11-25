#include "MessageFactoryFunctions.hpp"
#include <algorithm>

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
}


const char * createExitMessage()
{
    char * buffer = new char[5]();
    buffer[0] = 1;
    buffer[1] = 1;
    return buffer;
}

const char * createNonExitMessage()
{
    char * buffer = new char[5]();
    buffer[0] = 1;
    buffer[1] = 2;
    return buffer;
}

const char * createExitMessageWithWrongEndian()
{
    char * buffer = new char[5]();
    buffer[0] = 1;
    buffer[1] = 0;
    buffer[2] = 1;
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

}
