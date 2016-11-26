#include "MessageFactoryFunctions.hpp"
#include <algorithm>

namespace tests
{

const char * createExitMessage()
{
    char * buffer = new char[5]();
    buffer[0] = 1;
    buffer[1] = 1;
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

}
