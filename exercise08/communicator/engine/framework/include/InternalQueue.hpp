#pragma once

#include "IMessageReceiver.hpp"
#include <mutex>
#include <condition_variable>
#include <queue>

namespace framework
{
class InternalQueue : public IMessageReceiver
{
public:
    InternalQueue()
        : mutex(),
          conditional(),
          queue()
    {}
    void send(const char * message);
    void copyAndSend(int size, const char * message);
    const char * receive() override;
private:
    std::mutex mutex;
    std::condition_variable conditional;
    std::queue<const char *> queue;
};

}
