#ifndef list_file_hpp
#define list_file_hpp

#include "../../found_file/found_file.hpp"
#include "list_operator.hpp"
#include "file_model_column.hpp"
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/builder.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treestore.h>	
#include <gtkmm/liststore.h>
#include <gtkmm/treeiter.h>
#include <optional>
#include <string>
#include <sstream>
#include <memory>

class list_file: public std::shared_ptr<list_operator>, std::shared_ptr<file_column> {
	public:
		uint64_t _id = 0;
		list_file() = default;
		list_file(Glib::RefPtr<Gtk::Builder>& b, std::string label_name, std::string label_name_store);
		virtual ~list_file() = default;
		void add(found_file& f);
		void remove(found_file& f);
		void remove(uint32_t id);
		std::optional<Gtk::TreeModel::iterator> get_iter(uint32_t id);
	protected:
		//Member widgets:
	};

#endif // list_file_hpp
