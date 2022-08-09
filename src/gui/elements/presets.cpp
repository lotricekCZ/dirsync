#ifndef presets_cpp
#define presets_cpp

#include "presets.hpp"

presets::presets(Glib::RefPtr<Gtk::Builder> b, std::map<std::string, std::string> name, std::shared_ptr<variables> v){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	option_operation 	= Glib::RefPtr<Gtk::ComboBox>::cast_dynamic(b -> get_object(name["combobox"]));
	operations			= Glib::RefPtr<Gtk::ListStore>::cast_dynamic(b -> get_object(name["combo_list"]));
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	move	 = Glib::RefPtr<Gtk::Button>::cast_dynamic(b -> get_object(name["move"]));
	ignore	 = Glib::RefPtr<Gtk::Button>::cast_dynamic(b -> get_object(name["ignore"]));
	remove	 = Glib::RefPtr<Gtk::Button>::cast_dynamic(b -> get_object(name["remove"]));
	refresh	 = Glib::RefPtr<Gtk::Button>::cast_dynamic(b -> get_object(name["refresh"]));
	// set_functions();
	vars = v;

	auto contains = [](auto name, auto key){
		return (name.find(key) != name.end());
		};
	
	if(contains(name, "folder_add") && contains(name, "folder_remove") 
		&& contains(name, "folder_view") && contains(name, "folder_store")
		&& contains(name, "label_folder") && contains(name, "label_folder")) 
		e_folder = expander_folder(b, vars, 
			name["folder_add"], name["folder_remove"], 
			name["folder_view"], name["folder_store"],
			name["label_folder"], name["folder"]);
	else printf("insufficient parameters %s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	
	if(contains(name, "blacklist_add") && contains(name, "blacklist_remove") 
		&& contains(name, "blacklist_view") && contains(name, "blacklist_store")
		&& contains(name, "label_blacklist") && contains(name, "blacklist")) 
		e_blacklist = expander_blacklist(b, vars, 
			name["blacklist_add"], name["blacklist_remove"], 
			name["blacklist_view"], name["blacklist_store"], 
			name["label_blacklist"], name["blacklist"]);

	
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	operations -> set_column_types(view_column());
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	option_operation -> set_model(operations);
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	auto op_op = option_operation;
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	auto on_change = [this](){
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		vars -> set_view_mode((*option_operation -> get_active())[view_column().number]);
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		// this -> list_folder::clear_selected();
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		};
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);

	option_operation -> signal_changed().connect(on_change);
	}



void presets::fill(){
	// static_cast<>e_folder
	e_folder.fill();
	e_blacklist.fill();
	}



void presets::expander_folder::fill(){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<list_folder>> (*this) -> start();
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



void presets::expander_blacklist::fill(){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<list_blacklist>> (*this) -> start();
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



presets::expander::expander(Glib::RefPtr<Gtk::Builder> b, 
		std::string label_add, std::string label_remove, 
		std::string label, std::string number){
	// display_label.second -> set_text(std::to_string(label_value));
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	this -> add 	= Glib::RefPtr<Gtk::Button>::cast_dynamic(b -> get_object(label_add));
	this -> remove	= Glib::RefPtr<Gtk::Button>::cast_dynamic(b -> get_object(label_remove));
	this -> count	= double_text(b, label, number);
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



std::map<std::string, Glib::RefPtr<Gtk::Button>> presets::expander::get_buttons(){
	return std::map<std::string, Glib::RefPtr<Gtk::Button>>({{"add", add}, {"remove", remove}});
	}



std::map<std::string, Glib::RefPtr<Gtk::Button>> presets::expander_folder::get_buttons(){
	return static_cast<std::shared_ptr<presets::expander>>(*this) -> get_buttons();
	}



std::map<std::string, Glib::RefPtr<Gtk::Button>> presets::expander_blacklist::get_buttons(){
	return static_cast<std::shared_ptr<presets::expander>>(*this) -> get_buttons();
	}



presets::expander_folder::expander_folder(Glib::RefPtr<Gtk::Builder> b, std::shared_ptr<variables> vars,
		std::string label_add, std::string label_remove, 
		std::string label_name, std::string label_name_store,
		std::string label, std::string number): 
			std::shared_ptr<expander>	(new expander(b, label_add, label_remove, label, number)), 
			std::shared_ptr<list_folder>(new list_folder(b, label_name, label_name_store)){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<list_folder>> (*this) -> vars = vars;
	
	if(!(static_cast<std::shared_ptr<list_folder>>(*this))) printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	if(!(static_cast<std::shared_ptr<expander>>(*this))) printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);

	auto list_f = static_cast<std::shared_ptr<list_folder>> (*this);
	auto l_op = static_cast<std::shared_ptr<list_operator>> (*list_f); 
	auto fc = static_cast<std::shared_ptr<folder_column>> (*list_f);

	auto on_add = [list_f](){
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		list_f -> add();
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		};
	auto on_delete = [list_f](){
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		list_f -> clear_selected();
		// this -> list_folder::clear_selected();
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		};
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	auto on_edited = [this, fc, l_op] (const Glib::ustring& path, const Glib::ustring& new_text){
		auto iter = l_op -> get_iter(path);
		(*iter)[fc -> name] = new_text;
		};
	// display_label.second -> set_text(std::to_string(label_value));
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<expander>> (*this) -> add -> signal_clicked().connect(on_add);
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<expander>> (*this) -> remove -> signal_clicked().connect(on_delete);
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(b -> get_object("folder")) -> signal_edited().connect(on_edited);
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	// this -> expander::add -> signal_clicked().connect(on_add);
	// this -> expander::remove -> signal_clicked().connect(on_delete);
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	
	}



presets::expander_blacklist::expander_blacklist(Glib::RefPtr<Gtk::Builder> b, std::shared_ptr<variables> vars,
		std::string label_add, std::string label_remove, 
		std::string label_name, std::string label_name_store,
		std::string label, std::string number): 
			std::shared_ptr<expander>	(new expander(b, label_add, label_remove, label, number)),
			std::shared_ptr<list_blacklist>(new list_blacklist(b, label_name, label_name_store)){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<list_blacklist>> (*this) -> vars = vars;
	auto list_f = static_cast<std::shared_ptr<list_blacklist>> (*this);
	auto l_op = static_cast<std::shared_ptr<list_operator>> (*list_f); 
	auto fc = static_cast<std::shared_ptr<blacklist_column>> (*list_f);

	auto on_add = [list_f](){
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		list_f -> add();
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		};
	auto on_delete = [list_f](){
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		list_f -> clear_selected();
		// this -> list_folder::clear_selected();
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		};
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	auto on_edited = [this, fc, l_op] (const Glib::ustring& path, const Glib::ustring& new_text){
		auto iter = l_op -> get_iter(path);
		(*iter)[fc -> name] = new_text;
		};
	// display_label.second -> set_text(std::to_string(label_value));
	static_cast<std::shared_ptr<expander>> (*this) -> add -> signal_clicked().connect(on_add);
	static_cast<std::shared_ptr<expander>> (*this) -> remove -> signal_clicked().connect(on_delete);
	Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(b -> get_object("blacklist")) -> signal_edited().connect(on_edited);
	// this -> expander::add -> signal_clicked().connect(on_add);
	// this -> expander::remove -> signal_clicked().connect(on_delete);
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



std::map<std::string, std::any> presets::get_elements(){
	return std::map<std::string, std::any>({
		{"move", 		move},
		{"ignore", 		ignore},
		{"remove", 		remove},
		{"refresh", 	refresh},
		
		{"option", 		option_operation},
		{"operations", 	operations},
		{"temporary", 	temporary}
		});
	}



void presets::expander_folder::set_variables(std::shared_ptr<variables> vars){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<list_folder>> (*this) -> vars = vars;
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



void presets::expander_blacklist::set_variables(std::shared_ptr<variables> vars){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<list_blacklist>> (*this) -> vars = vars;
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}


#endif // presets_cpp