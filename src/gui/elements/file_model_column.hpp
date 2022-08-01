#ifndef file_model_column_hpp
#define file_model_column_hpp

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treemodel.h>
#include <glib.h>
#include <string>

class file_column : public Gtk::TreeModel::ColumnRecord{
	public:
		file_column() { add(id); add(selected); add(name); add(number); add(filetypes); add(color);}
		file_column(const file_column &) {add(id); add(selected); add(name); add(number); add(filetypes); add(color);}
		Gtk::TreeModelColumn<uint64_t> 			id;
		Gtk::TreeModelColumn<bool> 				selected;
		Gtk::TreeModelColumn<Glib::ustring> 	name;
		Gtk::TreeModelColumn<uint32_t>		 	number;
		Gtk::TreeModelColumn<Glib::ustring> 	filetypes;
		Gtk::TreeModelColumn<Glib::ustring> 	color;
	};

#endif // file_model_column