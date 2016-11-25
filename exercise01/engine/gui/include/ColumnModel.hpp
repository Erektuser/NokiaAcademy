#pragma once

#include <gtkmm.h>

namespace gui
{
class ColumnModel : public Gtk::TreeModelColumnRecord
{
public:
    ColumnModel()
    {
        add(statusColumn);
        add(nameColumn);
    }

    Gtk::TreeModelColumn<Glib::ustring> nameColumn;
    Gtk::TreeModelColumn<Glib::ustring> statusColumn;
};
}
