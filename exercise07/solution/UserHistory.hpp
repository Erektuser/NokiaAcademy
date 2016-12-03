#pragma once
#include "UserHistory.hpp"
#include <string>
#include <vector>
namespace solution
{

class IUserHistory
{
public:
    virtual ~IUserHistory() {};

    virtual const std::vector<std::string>& getHistory() const = 0;
    virtual void addToHistory(const std::string & hist) = 0;
    virtual unsigned int getHistoryCount() const = 0;

};

class UserHistory : public IUserHistory
{
public:
    const std::vector<std::string>& getHistory() const override;
    void addToHistory(const std::string & hist) override;
    unsigned int getHistoryCount() const override;
};

}
