#include "UserHistory.hpp"
#include <sstream>
#include <iostream>


namespace solution
{

const std::vector<std::string>& UserHistory::getHistory() const
{
    return history;
}

void UserHistory::addToHistory(const std::string & hist)
{
    history.push_back(hist);
}

unsigned int UserHistory::getHistoryCount() const
{
    return history.size();
}

}
