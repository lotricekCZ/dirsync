#ifndef list_blacklist_hpp
#define list_blacklist_hpp

#include "../../found_file/found_file.hpp"
#include "../../variables/variables.hpp"
#include "list_operator.hpp"
#include "blacklist_model_column.hpp"
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/builder.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treestore.h>	
#include <gtkmm/liststore.h>
#include <filesystem>
#include <string>
#include <memory>

class list_blacklist: public std::shared_ptr<list_operator>, 
				public std::shared_ptr<blacklist_column> {
	public:
		uint64_t _id = 0;
		bool edited;
		list_blacklist() = default;
		list_blacklist(Glib::RefPtr<Gtk::Builder>& b, std::string label_name, std::string label_name_store);
		std::shared_ptr<variables> vars;
		virtual ~list_blacklist() = default;
		void add(std::string& f);
		Gtk::TreeModel::iterator add();
		std::vector<bool> get_checked();
		void start();
		void clear();
		void clear_selected();
		// void remove(std::string& f);

	protected:
		//Member widgets:
	};

#endif // list_blacklist_hpp
