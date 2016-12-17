#pragma once
#include <Identity.hpp>
#include <UserHistory.hpp>
#include <map>

namespace solution
{

struct DataHolder
{
    bool running = true;
    std::map<framework::Identity, IUserHistory*> historyList;
    IUserHistory * currentUserSelection = nullptr;
    IUserHistory * getUserHistory(const framework::Identity id)
    {
        if(not historyList[id])
        {
            historyList[id] = new UserHistory;
        }
        return historyList[id];
    }
};

}