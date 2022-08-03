#ifndef list_operator_hpp
#define list_operator_hpp

#include "../../found_file/found_file.hpp"
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/builder.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treestore.h>	
#include <gtkmm/liststore.h>
#include <gtkmm/treemodelcolumn.h>
#include <string>
#include <memory>

class list_operator: public Glib::RefPtr<Gtk::TreeView>, 
	public Glib::RefPtr<Gtk::ListStore> {
	public:
		void set_column_types (const Gtk::TreeModel::ColumnRecord& columns);
		list_operator() = default;
		list_operator(Glib::RefPtr<Gtk::Builder> b, std::string label_name, std::string label_name_store);
		~list_operator() = default;
		void clear();
		Gtk::TreeModel::iterator erase(const Gtk::TreeModel::iterator& iter);
		Gtk::TreeModel::iterator get_iter(const Glib::ustring& path_string);
		Gtk::TreeModel::iterator add_row();
		Gtk::TreeModel::Children children();
		Gtk::TreeViewColumn* get_column(int n);
		template<typename ColumnType>
		int append_column(const Glib::ustring& title, 
				const Gtk::TreeModelColumn<ColumnType>& model_column);
		void set_model(const Glib::RefPtr<Gtk::TreeModel>& model);
	protected:
		//Member widgets:
	};

#endif // list_operator_hpp
