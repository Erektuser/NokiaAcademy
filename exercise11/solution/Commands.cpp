#include <Commands.hpp>
#include <IMessageSender.hpp>
#include <ITimerManager.hpp>
#include <IUserOutput.hpp>
#include <DataHolder.hpp>
#include <Identity.hpp>
#include <map>
#include <set>
#include <stdexcept>

namespace solution
{
using namespace framework;

class Commands : public ICommands
{
    std::map<MsgId, ICommand *> commands;
public:
    ~Commands()
    {
        for(auto command : commands)
        {
            delete command.second;
        }
    }
    template<typename T, typename... Args>
    ICommands& add(MsgId id, Args&&... args)
    {
        commands[id] = new T(std::forward<Args>(args)...);
        return *this;
    }
    ICommand & operator[](const MsgId id) override
    {
        auto&& it = commands.find(id);
        if(it == commands.end())
        {
            throw std::runtime_error("Command not found!!!");
        }
        return *(it->second);
    }
};

class ExitCommand : public ICommand
{
    std::shared_ptr<DataHolder> holder;
public:
    ExitCommand(const std::shared_ptr<DataHolder> & holder)
    :   holder(holder)
    {}
    void operator()(const Message & msg) override
    {
        holder->running = false;
    }
};

class TimerExpiryCommand :  public ICommand
{
    bool isIdentityOnList(Identity id)
    {
        return identityList.count(id);
    }

    void addIdentityToList(Identity id)
    {
        identityList.insert(id);
        userOutput->addRecipient(std::to_string(id));
    }

    std::shared_ptr<framework::IMessageSender> messageSender;
    std::shared_ptr<framework::IUserOutput> userOutput;
    std::shared_ptr<framework::ITimerManager> timerManager;
    std::set<Identity> identityList;
    int timerId = 0;
public:
    TimerExpiryCommand(const std::shared_ptr<framework::IMessageSender> & sender,
                       const std::shared_ptr<framework::IUserOutput> & userOutput,
                       const std::shared_ptr<framework::ITimerManager> & timerManager)
    :   messageSender(sender),
        userOutput(userOutput),
        timerManager(timerManager)
    {}
    void operator()(const Message & msg) override
    {
        auto&& addresses = messageSender->getAddresses();
        for(auto address : addresses)
        {
            if(isIdentityOnList(address))
            {
                continue;
            }
            addIdentityToList(address);
        }
        timerId = timerManager->startTimer(1000);
    }
};

class InternalTextCommand : public ICommand
{
    std::shared_ptr<framework::IUserOutput> userOutput;
    std::shared_ptr<framework::IMessageSender> messageSender;
    std::shared_ptr<DataHolder> dataHolder;
public:
    InternalTextCommand(const std::shared_ptr<framework::IUserOutput> & userOutput,
                        const std::shared_ptr<framework::IMessageSender> & messageSender,
                        const std::shared_ptr<DataHolder> & dataHolder)
    :   userOutput(userOutput),
        messageSender(messageSender),
        dataHolder(dataHolder)
    {}
    void operator()(const Message & msg) override
    {
        const std::size_t size = msg.body.internal.msgData.msgUserInput.size;
        const std::string text {msg.body.internal.msgData.msgUserInput.data, size};

	const framework::Identity id = dataHolder->getSelectedUserId();
        if (id)
        {
	    userOutput->print("[Me] " + text);
            messageSender->sendTo(id, size + 4, reinterpret_cast<const char *>(&msg) + 1);
        }
    }
};

class UserSelectionCommand : public ICommand
{
    std::shared_ptr<solution::DataHolder> holder;
    std::shared_ptr<framework::IUserOutput> userOutput;
public:
    UserSelectionCommand(const std::shared_ptr<solution::DataHolder> & holder,
                         const std::shared_ptr<framework::IUserOutput> & userOutput)
    :   holder(holder),
        userOutput(userOutput) {}
    void operator()(const Message & msg) override
    {
        const std::size_t size = msg.body.internal.msgData.msgUserInput.size;
        const std::string text {msg.body.internal.msgData.msgUserInput.data, size};
        userOutput->clearOutput();
        holder->currentUserSelection = holder->getUserHistory(std::stoll(text));
        if(holder->currentUserSelection)
        {
            auto&& history = holder->currentUserSelection->getHistory();
            for(const auto& entry : history)
            {
                userOutput->print(entry);
            }
            userOutput->setRecipientStatus(text, ' ');
        }
    }
};

class ExternalTextCommand : public ICommand
{
    std::shared_ptr<solution::DataHolder> holder;
    std::shared_ptr<framework::IUserOutput> userOutput;
public:
    ExternalTextCommand(const std::shared_ptr<solution::DataHolder> & holder,
                        const std::shared_ptr<framework::IUserOutput> & userOutput)
    :   holder(holder),
        userOutput(userOutput) {}
    void operator()(const Message & msg) override
    {
        const Identity id = *reinterpret_cast<const framework::Identity*>(&(msg.body.external.identity));
        IUserHistory * userHist = holder->getUserHistory(id);
        if(not holder->currentUserSelection)
        {
            holder->currentUserSelection = userHist;
            userOutput->setRecipientStatus(std::to_string(id), '!');
        }
        const std::size_t size = msg.body.external.size;
        const std::string text {msg.body.external.data, size};
        const std::string buffer = "[unknown] " + text;
        if (holder->currentUserSelection == userHist)
        {
            userOutput->print(buffer);
        }
        else
        {
            userOutput->setRecipientStatus(std::to_string(id), '!');
        }
        userHist->addToHistory(buffer);
    }
};

CommandsPtr createCommands(
        std::shared_ptr<solution::DataHolder> holder,
        std::shared_ptr<framework::IMessageReceiver> receiver,
        std::shared_ptr<framework::IMessageSender> sender,
        std::shared_ptr<framework::IUserOutput> userOutput,
        std::shared_ptr<framework::ITimerManager> timerManager)
{
    std::unique_ptr<Commands> internalCommands(new Commands);
    internalCommands->add<ExitCommand>(MsgId::Exit, holder);
    internalCommands->add<TimerExpiryCommand>(MsgId::Timer, sender, userOutput, timerManager);
    internalCommands->add<InternalTextCommand>(MsgId::Text, userOutput, sender, holder);
    internalCommands->add<UserSelectionCommand>(MsgId::UserSelected, holder, userOutput);

    std::unique_ptr<Commands> externalCommands(new Commands);
    externalCommands->add<ExternalTextCommand>(MsgId::Text, holder, userOutput);
    return std::move(std::make_tuple(std::move(internalCommands),
                                     std::move(externalCommands)));
}

}
