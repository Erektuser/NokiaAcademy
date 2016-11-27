#pragma once

#include <gtkmm.h>
#include <mutex>
#include <condition_variable>

namespace gui
{
using Call = std::function<void ()>;

class Dispatcher
{
public:
    Dispatcher()
    {
        dispatcher.connect(sigc::mem_fun(*this,&Dispatcher::handle));
    }
    void dispatch(Call call);

private:
    void handle();

    Glib::Dispatcher dispatcher;
    Call call;
    std::mutex mutex;
    std::mutex entry_mutex;
    std::condition_variable conditional;
};

}
