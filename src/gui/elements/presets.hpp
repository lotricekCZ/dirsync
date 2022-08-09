#ifndef presets_hpp
#define presets_hpp

#include "../../found_file/found_file.hpp"
#include "../../variables/variables.hpp"
#include "double_text.hpp"
#include "list_operator.hpp"
#include "folder_model_column.hpp"
#include "view_model_column.hpp"
#include "list_folder.hpp"
#include "list_blacklist.hpp"
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/builder.h>
#include <gtkmm/combobox.h>
#include <gtkmm/filechooser.h>
#include <string>
#include <map>
#include <any>

class presets {
	public:
		presets(Glib::RefPtr<Gtk::Builder> , 
			std::map<std::string, std::string>,
			std::shared_ptr<variables>);
		presets() = default;
		virtual ~presets() = default;

		Glib::RefPtr<Gtk::Button> 		move;
		Glib::RefPtr<Gtk::Button> 		ignore;
		Glib::RefPtr<Gtk::Button> 		remove;
		Glib::RefPtr<Gtk::Button> 		refresh;

		Glib::RefPtr<Gtk::ComboBox> 	option_operation;
		Glib::RefPtr<Gtk::ListStore>	operations;
		Glib::RefPtr<Gtk::FileChooser> 	temporary;

		view_column view_mode();
		void fill();
		std::map<std::string, std::any> get_elements();
		std::shared_ptr<variables> vars;

		class expander {
			public:
				expander(Glib::RefPtr<Gtk::Builder> b, 
						std::string label_add, std::string label_remove, 
						std::string label, std::string number);
				expander() = default;
				std::map<std::string, Glib::RefPtr<Gtk::Button>> get_buttons();
				// Glib::RefPtr<Gtk::SearchEntry> search;
				Glib::RefPtr<Gtk::Button> add;
				Glib::RefPtr<Gtk::Button> remove;
				double_text count;
			};
		
		class expander_folder: public std::shared_ptr<expander>, public std::shared_ptr<list_folder> {
			public:
				// using list_folder::add;
				expander_folder(Glib::RefPtr<Gtk::Builder> b, std::shared_ptr<variables> vars, 
					std::string label_add, std::string label_remove, 
					std::string label_name, std::string label_name_store,
					std::string label, std::string number);
				std::map<std::string, Glib::RefPtr<Gtk::Button>> get_buttons();
				void fill();
				expander_folder() = default;
				void set_variables(std::shared_ptr<variables> vars);
			} e_folder;
		
		class expander_blacklist: public std::shared_ptr<expander>, public std::shared_ptr<list_blacklist> {
			public:
				expander_blacklist(Glib::RefPtr<Gtk::Builder> b, std::shared_ptr<variables> vars, 
					std::string label_add, std::string label_remove, 
					std::string label_name, std::string label_name_store,
					std::string label, std::string number);
				expander_blacklist() = default;
				std::map<std::string, Glib::RefPtr<Gtk::Button>> get_buttons();
				void fill();
				void set_variables(std::shared_ptr<variables> vars);
			} e_blacklist;
	protected:
		// std::pair<Glib::RefPtr<Gtk::Label>, Glib::RefPtr<Gtk::Label>> display_label;
		//Member widgets:
	};

#endif // presets_hpp