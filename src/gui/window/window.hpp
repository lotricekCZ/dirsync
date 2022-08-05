#ifndef window_hpp
#define window_hpp

#include <type_traits>
#include <thread>
#include <map>
#include <typeinfo>
#include <cinttypes>
#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/builder.h>
#include <glibmm/main.h>
#include "../../found_file/found_file.hpp"
#include "../elements/double_text.hpp"
#include "../elements/list_operator.hpp"
#include "../elements/list_file.hpp"
#include "../elements/presets.hpp"


class window: public Gtk::ApplicationWindow {
		class list_file_window {
			public:
				list_file_window(Glib::RefPtr<Gtk::Builder> b, std::map<std::string, std::string> in);
				std::map<std::string, std::any> elements = {
					{"list", 				std::shared_ptr<list_file>()},
					{"selected",			std::shared_ptr<double_text>()},
					{"unique", 				std::shared_ptr<double_text>()},
					{"total", 				std::shared_ptr<double_text>()}
					};
			};
		Gtk::Box *cont;
		Glib::RefPtr<Gtk::Builder> ui;
		std::map<std::string, std::string> names = {
			{"combobox",			"mode_file_show"},
			{"combo_list",			"mode"},

			{"move",				"button_move"},
			{"ignore",				"button_ignore"},
			{"remove",				"button_delete"},
			{"refresh",				"button_refresh"},

			{"folder_add",			"folder_add"}, 
			{"folder_remove",		"folder_remove"}, 
			{"folder_view",			"folder_listed"},
			{"folder_store",		"folder_selected"},	
			
			{"blacklist_add",		"blacklist_add"}, 
			{"blacklist_remove",	"blacklist_remove"}, 
			{"blacklist_view",		"blacklist_listed"},
			{"blacklist_store",		"blacklist_selected"},

			{"list",				"files_listed"},
			{"store",				"files_selected"},

			{"selected",			"label_num_selected_files"},
			{"selected_count",		"num_selected_files"},
			{"total",				"label_num_total_files"},
			{"total_count",			"num_total_files"},
			{"unique",				"label_num_unique_files"},
			{"unique_count",		"num_unique_files"}
			};

		std::map<std::string, std::any> elements = {
			{"presets", 			std::shared_ptr<presets>()},
			{"files", 				std::shared_ptr<list_file_window>()}
			};
		bool on_timeout();
	public:
		std::shared_ptr<variables> variable_table;
		presets pres;
		window(std::shared_ptr<variables> vars);
		
	};

#endif // window_hpp