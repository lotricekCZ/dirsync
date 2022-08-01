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
		file_column() { add(id); add(selected); add(name);}
		file_column(const file_column &) {add(id); add(selected); add(name);}
		Gtk::TreeModelColumn<uint64_t> 			id;
		Gtk::TreeModelColumn<bool> 				selected;
		Gtk::TreeModelColumn<Glib::ustring> 	name;
	};

#endif // folder_model_column