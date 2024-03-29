#ifndef folder_model_column_hpp
#define folder_model_column_hpp

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treemodel.h>
#include <glib.h>
#include <string>

class folder_column : public Gtk::TreeModel::ColumnRecord{
	public:
		folder_column() {add(editable); add(selected); add(name);}
		folder_column(const folder_column &) {add(editable);add(selected); add(name);}
		Gtk::TreeModelColumn<bool> 				editable;
		Gtk::TreeModelColumn<bool> 				selected;
		Gtk::TreeModelColumn<Glib::ustring> 	name;
	};

#endif // folder_model_column