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
#include "../../yaml_worker/yaml_worker.hpp"
#include "../../file_list/file_list.hpp"
#include "../elements/double_text.hpp"
#include "../elements/list_operator.hpp"
#include "../elements/list_file.hpp"
#include "../elements/presets.hpp"


class window: public Gtk::ApplicationWindow {
		class list_file_window {
			public:
				list_file_window(Glib::RefPtr<Gtk::Builder> b, 
								std::map<std::string, std::string> in, 
								std::shared_ptr<file_list> back);
				std::map<std::string, std::any> elements = {
					{"list", 				std::shared_ptr<list_file>()},
					{"selected",			std::shared_ptr<double_text>()},
					{"unique", 				std::shared_ptr<double_text>()},
					{"total", 				std::shared_ptr<double_text>()},
					{"variables", 			std::shared_ptr<variables>()},
					{"backend",				std::shared_ptr<file_list>()}
					};
				
				void set_variables(std::shared_ptr<variables> vars);
				void connect_event(std::shared_ptr<presets> pres, std::shared_ptr<yaml_worker> worker);
				void draw();
				void clear();
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
			{"temporary",			"temporary_chooser"},

			{"folder_add",			"folder_add"}, 
			{"folder_remove",		"folder_remove"}, 
			{"folder_view",			"folder_listed"},
			{"folder_store",		"folder_selected"},	
			{"label_folder",		"label_num_folder"},
			{"folder",				"num_folder"},

			{"blacklist_add",		"blacklist_add"}, 
			{"blacklist_remove",	"blacklist_remove"}, 
			{"blacklist_view",		"blacklist_listed"},
			{"blacklist_store",		"blacklist_selected"},
			{"label_blacklist",		"label_num_blacklist"},
			{"blacklist",			"num_blacklist"},

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
		bool check_changes();
	public:
		std::shared_ptr<variables> variable_table;
		std::shared_ptr<yaml_worker> worker;
		// presets pres;
		void fill();
		void start();
		window(std::shared_ptr<variables> vars, std::shared_ptr<file_list> back, std::shared_ptr<yaml_worker> work);
		
	};

#endif // window_hpp