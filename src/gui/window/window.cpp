#include "window.hpp"

window::window(std::shared_ptr<variables> vars, std::shared_ptr<file_list> back)
		: ui{Gtk::Builder::create_from_file("../src/gui/window/window.glade")} {
	if(ui) {
		this -> variable_table = vars;
	
		ui -> add_from_file("../src/gui/window/window.glade");
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		
		elements["presets"] = 	std::shared_ptr<presets>(new presets(ui, names, vars));
		elements["files"] = 	std::shared_ptr<list_file_window>(new list_file_window(ui, names, back));
		std::any_cast<std::shared_ptr<list_file_window>>(elements["files"]) -> set_variables(vars);
		
		// pres.e_folder = presets::expander_folder(ui, variable_table, "add", "remove", "paths_listed", "folder_selected");
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		ui -> get_widget<Gtk::Box>("window", cont);
		int timeout_value = 2500; // in ms (1.5 sec)
		sigc::slot<bool> my_slot = sigc::mem_fun(*this, &window::on_timeout);
		Glib::signal_timeout().connect(my_slot, timeout_value);
		add(*cont);
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		}
	show_all();
	}



bool window::on_timeout(){
	// d.set_value(i++);
	try {
		static_cast<std::shared_ptr<list_folder>>(
			std::any_cast<std::shared_ptr<presets>>(elements["presets"]) -> e_folder) -> print();
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		} catch (...){
			printf("Failed\n");
			}
	return true;
	}






void window::fill(){
	// d.set_value(i++);
	(std::any_cast<std::shared_ptr<presets>>(elements["presets"])) -> fill();
	(std::any_cast<std::shared_ptr<list_file_window>>(elements["files"])) -> draw();
	}



window::list_file_window::list_file_window(Glib::RefPtr<Gtk::Builder> b, 
		std::map<std::string, std::string> in, std::shared_ptr<file_list> back){
	
	elements["list"] =		std::shared_ptr<list_file>(new list_file(b, in["list"], in["store"]));
	elements["selected"] =	std::shared_ptr<double_text>(new double_text(b, in["selected"], in["selected_count"]));
	elements["total"] =		std::shared_ptr<double_text>(new double_text(b, in["total"], in["total_count"]));
	elements["unique"] =	std::shared_ptr<double_text>(new double_text(b, in["unique"], in["unique_count"]));
	elements["backend"] =	back;
	}



void window::list_file_window::draw(){
	for(auto &i: *std::any_cast<std::shared_ptr<file_list>>(elements["backend"])){
		// printf("%s", i.print().c_str());
		std::any_cast<std::shared_ptr<list_file>>(elements["list"]) -> add(i);
		}
	}



void window::list_file_window::connect_event(std::shared_ptr<presets> pres){
	// std::shared_ptr<
	auto ping = [](){
		printf("\n\n\n\033[91mPinged\033[0m\n\n\n");
		};
	auto butts = pres -> e_folder.get_buttons();
	butts["add"] -> signal_clicked().connect(ping);
	butts["remove"] -> signal_clicked().connect(ping);
	}



void window::list_file_window::set_variables(std::shared_ptr<variables> vars){

	}