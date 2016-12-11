#include "Dispatcher.hpp"

namespace gui
{
void Dispatcher::dispatch(Call call)
{
    std::lock_guard<std::mutex> entry_lock(entry_mutex);
    this->call = call;
    dispatcher();
    {
       std::unique_lock<std::mutex> lock(mutex);
       conditional.wait(lock, [=] { return !this->call;});
    }
}

void Dispatcher::handle()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (call)
        call();

    call = nullptr;

    conditional.notify_one();
}
}
