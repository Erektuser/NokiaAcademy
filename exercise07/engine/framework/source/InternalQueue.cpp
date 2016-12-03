#include "InternalQueue.hpp"
#include "MessageTypes.hpp"
#include <iostream>

namespace framework
{

void InternalQueue::send(const char *message)
{
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(message);
    conditional.notify_one();
}

void InternalQueue::copyAndSend(int size, const char *message)
{
    char * buffer = new char[size + 1];

    buffer[0] = static_cast<char>(MessageType::INTERNAL);

    std::copy(message, message + size, buffer + 1);

    send(buffer);
}



const char * InternalQueue::receive()
{
    std::unique_lock<std::mutex> lock(mutex);
    conditional.wait(lock, [&] { return not queue.empty();});
    const char * result = queue.front();
    queue.pop();
    return result;
}

}
