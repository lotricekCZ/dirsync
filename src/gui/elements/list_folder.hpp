#ifndef list_folder_hpp
#define list_folder_hpp

#include "../../found_file/found_file.hpp"
#include "../../variables/variables.hpp"
#include "list_operator.hpp"
#include "folder_model_column.hpp"
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/builder.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treestore.h>	
#include <gtkmm/liststore.h>
#include <filesystem>
#include <string>
#include <memory>
#include <optional>

class list_folder: public std::shared_ptr<list_operator>, 
				public std::shared_ptr<folder_column> {
	public:
		uint64_t _id = 0;
		bool edited = 0;
		list_folder() = default;
		list_folder(Glib::RefPtr<Gtk::Builder>& b, std::string label_name, std::string label_name_store);
		std::shared_ptr<variables> vars;
		virtual ~list_folder() = default;
		void add(std::filesystem::path& f);
		std::optional<Gtk::TreeModel::iterator> add();
		void clear();
		void print();
		void start();
		std::vector<bool> get_checked();
		void clear_selected();
		// void remove(std::filesystem::path& f);

	protected:
		//Member widgets:
	};

#endif // list_folder_hpp
