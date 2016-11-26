#include "MainWindow.hpp"

namespace
{
void removeEndLineChars(std::string& msg)
{
    int i = msg.size() - 1;
    while ((i >= 0) && (msg[i] == '\r' || msg[i] == '\n'))
    {
        --i;
    }
    msg.erase(i+1);
}
}

namespace gui
{
MainWindow::MainWindow(std::shared_ptr<framework::IInternalMessageSender> loopback)
    : mainBox(Gtk::ORIENTATION_VERTICAL),
      horizontalBox(Gtk::ORIENTATION_HORIZONTAL),
      hseparator1(Gtk::ORIENTATION_HORIZONTAL),
      hSeparator2(Gtk::ORIENTATION_HORIZONTAL),
      vSeparator(Gtk::ORIENTATION_VERTICAL),
      dispatcher(),
      clearBuffer(),
      loopback(loopback)
{
    set_title("Communicator");
    set_border_width(1);
    set_default_size(400, 200);
    set_resizable(false);
    add(mainBox);

    mainBox.pack_start(mainLabel);
    mainBox.pack_start(hseparator1);
    mainBox.pack_start(horizontalBox);
    mainBox.pack_start(hSeparator2);
    mainBox.pack_start(inputTextView);

    horizontalBox.pack_start(connectionsScrolledWindow);
    horizontalBox.pack_start(vSeparator);
    horizontalBox.pack_start(outputScrolledWindow);
    horizontalBox.set_vexpand(true);
    horizontalBox.set_size_request(-1, 450);

    mainLabel.set_size_request(-1,75);
    mainLabel.set_vexpand(false);
    hseparator1.set_vexpand(false);
    hseparator1.property_expand().set_value(false);

    inputTextView.set_vexpand(false);
    inputTextView.set_size_request(-1,150);
    inputTextView.set_hexpand(false);

    inputTextView.get_buffer()->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::handleInputChange),false);

    listStore = Gtk::ListStore::create(columnModel);

    connectionsScrolledWindow.add(connectionList);
    connectionsScrolledWindow.set_size_request(225,-1);
    connectionList.set_hexpand(false);
    connectionList.set_vexpand(true);
    connectionList.set_size_request(225,-1);
    connectionList.set_model(listStore);
    connectionList.append_column(" ", columnModel.statusColumn);
    connectionList.append_column("Recipient", columnModel.nameColumn);
    connectionList.get_selection()->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::handleReceipentSelection));

    vSeparator.set_hexpand(false);
    vSeparator.set_size_request(5,-1);

    outputScrolledWindow.add(outputTextView);
    outputScrolledWindow.set_size_request(450,-1);

    outputTextView.set_size_request(450,-1);
    outputTextView.property_editable().set_value(false);
    outputTextView.property_expand().set_value(false);
    outputTextView.set_vscroll_policy(Gtk::SCROLL_NATURAL);

    property_has_resize_grip().set_value(false);

    show_all_children();

    signal_delete_event().connect(sigc::mem_fun(*this, &MainWindow::handleClose), false);
    clearBuffer.connect(sigc::mem_fun(*this, &MainWindow::clearInput));
}

void MainWindow::addRecipientToList(const std::string &recipient)
{
    Gtk::TreeModel::iterator iter = listStore->append();
    Gtk::TreeModel::Row row = *iter;
    row[columnModel.nameColumn] = recipient;
    row[columnModel.statusColumn] = " ";
}

void MainWindow::updateRecipientStatus(const std::string &recipient, char status)
{
    Gtk::TreeModel::Children children = listStore->children();
    for(auto& child : children)
    {
        Gtk::TreeModel::Row row = *child;
        if (row[columnModel.nameColumn] == recipient)
        {
            std::string stat {status};
            row[columnModel.statusColumn] = stat;
        }
    }
}

void MainWindow::writeToOutput(const std::string &text)
{
    Glib::RefPtr<Gtk::Adjustment> adj = outputScrolledWindow.get_vadjustment();
    adj->set_value(adj->get_upper());
    outputTextView.get_buffer()->insert(outputTextView.get_buffer()->end(),text + "\n");
}

void MainWindow::print(const std::string& message)
{
    dispatcher.dispatch([=]{ writeToOutput(message);});
}

void MainWindow::addRecipient(const std::string &receipent)
{
    dispatcher.dispatch([=]{addRecipientToList(receipent);});
}

void MainWindow::setRecipientStatus(const std::string &receipent, char status)
{
    dispatcher.dispatch([=]{updateRecipientStatus(receipent, status);});
}

void MainWindow::setClearStatus(const std::string &status)
{
    dispatcher.dispatch([=]{mainLabel.set_text(status);});
}

void MainWindow::setErrorStatus(const std::string &status)
{
    dispatcher.dispatch([=]{mainLabel.set_text(status);});
}

void MainWindow::clearOutput()
{
    dispatcher.dispatch(([=]{clearOutputBuffer();}));
}

void MainWindow::clearOutputBuffer()
{
    Glib::RefPtr<Gtk::TextBuffer> buffer = outputTextView.get_buffer();
    buffer->erase(buffer->begin(),buffer->end());
}

void MainWindow::handleReceipentSelection()
{
    Gtk::TreeModel::iterator iter = connectionList.get_selection()->get_selected();
    Gtk::TreeModel::Row row = *iter;

    Glib::ustring strText = row[columnModel.nameColumn];
    std::string receipent = strText;

    loopback->sendSetRecipient(receipent);
}

void MainWindow::handleInputChange()
{
    if (inputTextView.get_buffer()->get_line_count() > 1)
    {
        std::string msg = inputTextView.get_buffer()->get_text();
        removeEndLineChars(msg);
        loopback->sendTextMessage(msg);
        clearBuffer();
    }
}

bool MainWindow::handleClose(GdkEventAny *)
{
    loopback->sendExitMessage();
    return false;
}

void MainWindow::clearInput()
{
    inputTextView.get_buffer()->set_text("");
}

}
