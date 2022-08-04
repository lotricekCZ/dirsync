#ifndef view_model_column_hpp
#define view_model_column_hpp

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treemodel.h>
#include <glib.h>
#include <string>

class view_column : public Gtk::TreeModel::ColumnRecord{
	public:
		view_column() { add(name); add(number);}
		view_column(const view_column &) {add(name); add(number);}
		Gtk::TreeModelColumn<Glib::ustring> 	name;
		Gtk::TreeModelColumn<uint32_t>		 	number;
	};

#endif // view_model_column