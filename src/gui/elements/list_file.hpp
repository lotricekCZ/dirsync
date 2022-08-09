#ifndef list_file_hpp
#define list_file_hpp

#include "../../found_file/found_file.hpp"
#include "../../file_list/file_list.hpp"
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
#include <vector>
#include <memory>

class list_file: public std::shared_ptr<list_operator>, std::shared_ptr<file_column> {
	public:
		uint64_t _id = 0;
		std::shared_ptr<file_list> real_files;
		list_file() = default;
		list_file(Glib::RefPtr<Gtk::Builder>& b, std::string label_name, std::string label_name_store);
		virtual ~list_file() = default;
		void add(found_file& f);
		void remove(found_file& f);
		void remove(uint32_t id);
		std::optional<Gtk::TreeModel::iterator> get_iter(uint32_t id);
		std::vector<bool> get_checked();
		void clear_selected();
	protected:
		//Member widgets:
	};

#endif // list_file_hpp
