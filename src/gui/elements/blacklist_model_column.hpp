#ifndef blacklist_model_column_hpp
#define blacklist_model_column_hpp

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treemodel.h>
#include <glib.h>
#include <string>

class blacklist_column : public Gtk::TreeModel::ColumnRecord{
	public:
		blacklist_column() {add(editable); add(selected); add(name);}
		blacklist_column(const blacklist_column &) {add(editable); add(selected); add(name);}
		Gtk::TreeModelColumn<bool> 				editable;
		Gtk::TreeModelColumn<bool> 				selected;
		Gtk::TreeModelColumn<Glib::ustring> 	name;
	};

#endif // blacklist_model_column