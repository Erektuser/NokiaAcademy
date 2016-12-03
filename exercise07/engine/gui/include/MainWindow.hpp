#pragma once

#include <gtkmm.h>
#include <string>
#include <memory>
#include <Dispatcher.hpp>
#include <ColumnModel.hpp>
#include "IUserOutput.hpp"
#include "IInternalMessageSender.hpp"

namespace gui
{
class MainWindow : public Gtk::Window, public framework::IUserOutput
{
public:
    MainWindow(std::shared_ptr<framework::IInternalMessageSender> loopback);
    void print(const std::string& message) override;
    void addRecipient(const std::string& receipent) override;
    void setRecipientStatus(const std::string& receipent, char status) override;
    void setClearStatus(const std::string& status) override;
    void setErrorStatus(const std::string& status) override;
    void clearOutput() override;


private:
    void handleInputChange();
    void handleReceipentSelection();
    bool handleClose(GdkEventAny*);
    void clearInput();
    void addRecipientToList(const std::string &recipient);
    void updateRecipientStatus(const std::string &recipient, char status);
    void writeToOutput(const std::string& text);
    void clearOutputBuffer();

    Gtk::Box mainBox;
    Gtk::Box horizontalBox;
    Gtk::Label mainLabel;
    Gtk::Separator hseparator1;
    Gtk::Separator hSeparator2;
    Gtk::Separator vSeparator;
    Gtk::TextView inputTextView;
    Gtk::TreeView connectionList;
    ColumnModel columnModel;
    Glib::RefPtr<Gtk::ListStore> listStore;
    Gtk::TextView outputTextView;
    Gtk::ScrolledWindow outputScrolledWindow;
    Gtk::ScrolledWindow connectionsScrolledWindow;

    Dispatcher dispatcher;
    Glib::Dispatcher clearBuffer;

    std::shared_ptr<framework::IInternalMessageSender> loopback;

};

}
