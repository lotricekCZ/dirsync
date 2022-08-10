#include "window.hpp"

window::window(std::shared_ptr<variables> vars, std::shared_ptr<file_list> back, std::shared_ptr<yaml_worker> work)
		: ui{Gtk::Builder::create_from_file("../src/gui/window/window.glade")} {
	if(ui) {
		this -> variable_table = vars;
		worker = work;
		ui -> add_from_file("../src/gui/window/window.glade");
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		
		elements["presets"] = 	std::shared_ptr<presets>(new presets(ui, names, vars));
		elements["files"] = 	std::shared_ptr<list_file_window>(new list_file_window(ui, names, back));
		std::any_cast<std::shared_ptr<list_file_window>>(elements["files"]) -> set_variables(vars);
		std::any_cast<std::shared_ptr<list_file_window>>(elements["files"]) 
			-> connect_event(std::any_cast<std::shared_ptr<presets>>(elements["presets"]), worker);
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



bool window::check_changes(){
	// auto dirIter = std::filesystem::directory_iterator("directory_path");

	// int fileCount = std::count_if(
	// 	begin(dirIter),
	// 	end(dirIter),
	// 	[](auto& entry) { return entry.is_regular_file(); }
	// );
	// d.set_value(i++);
	try {
		
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



void window::list_file_window::connect_event(std::shared_ptr<presets> pres, std::shared_ptr<yaml_worker> worker){
	auto _pres = pres;
	auto _vars = 	std::any_cast<std::shared_ptr<variables>>(elements["variables"]);
	auto _files = 	std::any_cast<std::shared_ptr<file_list>>(elements["backend"]);
	auto _list = 	std::any_cast<std::shared_ptr<list_file>>(elements["list"]);
	auto _worker = 	worker;

	auto save_and_reload = [this, _pres, _vars, _files, _list, _worker](){
		printf("\n\n\n\033[91mPinged\033[0m\n\n\n");
		// std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		for(auto o: _vars -> get_directories())
			std::cout << o.string() << std::endl;
		for(auto o: *_vars -> dir_list)
			std::cout << o.string() << std::endl;
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		printf("SIZE 2: %i\n", _vars -> dir_list -> size());
		_worker -> write();
		for(auto o: _vars -> get_directories())
			std::cout << o.string() << std::endl;
		for(auto o: *_vars -> dir_list)
			std::cout << o.string() << std::endl;
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		};


	auto get_selected = [this, _pres, _vars, _files, _list](){
		printf("\n\n\n\033[91mPinged\033[0m\n\n\n");
		auto ids = _list -> clear_selected();
		auto indexes = _files -> get_indexes(ids);

		printf("\n\n\n\033[91mPinged\033[0m\n");
		printf("\033[91mSIZE\t%i\033[0m\n\n\n", ids.size());
		while(indexes.size()){
			found_file f = _files -> at(indexes.back());
			f.tick_all();
			for(auto it = f.occurences.begin(); it != f.occurences.end(); it++) {
				if(it -> first)
					printf("MOVING %s to %s\n", it -> second.filename().c_str(), _vars -> get_temporary().c_str());
					std::filesystem::rename(it -> second, _vars -> get_temporary()/(it -> second.filename()));	
				}
			// std::filesystem::rename()
			indexes.pop_back();
			}
		};



	auto els_pres = pres -> get_elements();
	auto bl = std::any_cast<presets::expander_blacklist>(els_pres["blacklist"]).get_buttons();
	auto fd = std::any_cast<presets::expander_folder>(els_pres["folders"]).get_buttons();
	

	bl["add"] -> signal_clicked().connect(save_and_reload);
	bl["remove"] -> signal_clicked().connect(save_and_reload);

	fd["add"] -> signal_clicked().connect(save_and_reload);
	fd["remove"] -> signal_clicked().connect(save_and_reload);

	std::any_cast<Glib::RefPtr<Gtk::Button>>(els_pres["move"]) -> signal_clicked().connect(get_selected);
	// std::any_cast<Glib::RefPtr<Gtk::Button>>(els_pres["move"]) -> signal_clicked().connect(get_selected);
	}



void window::list_file_window::set_variables(std::shared_ptr<variables> vars){
	elements["variables"] = vars;
	}