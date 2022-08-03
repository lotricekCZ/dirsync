#ifndef presets_cpp
#define presets_cpp

#include "presets.hpp"

presets::presets(Glib::RefPtr<Gtk::Builder> b, std::string label_option, std::string label_options){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	option_operation 	= Glib::RefPtr<Gtk::ComboBox>::cast_dynamic(b -> get_object(label_option));
	operations			= Glib::RefPtr<Gtk::ListStore>::cast_dynamic(b -> get_object(label_options));
	option_operation -> set_model(operations);
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



presets::expander::expander(Glib::RefPtr<Gtk::Builder> b, 
		std::string label_add, std::string label_remove){
	// display_label.second -> set_text(std::to_string(label_value));
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	this -> add 	= Glib::RefPtr<Gtk::Button>::cast_dynamic(b -> get_object(label_add));
	this -> remove	= Glib::RefPtr<Gtk::Button>::cast_dynamic(b -> get_object(label_remove));
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



presets::expander_folder::expander_folder(Glib::RefPtr<Gtk::Builder> b, std::shared_ptr<variables> vars,
		std::string label_add, std::string label_remove, 
		std::string label_name, std::string label_name_store): 
			std::shared_ptr<expander>	(new expander(b, label_add, label_remove)), 
			std::shared_ptr<list_folder>(new list_folder(b, label_name, label_name_store)){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<list_folder>> (*this) -> vars = vars;
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
	static_cast<std::shared_ptr<expander>> (*this) -> add -> signal_clicked().connect(on_add);
	static_cast<std::shared_ptr<expander>> (*this) -> remove -> signal_clicked().connect(on_delete);
	Glib::RefPtr<Gtk::CellRendererText>::cast_dynamic(b -> get_object("folder")) -> signal_edited().connect(on_edited);
	// this -> expander::add -> signal_clicked().connect(on_add);
	// this -> expander::remove -> signal_clicked().connect(on_delete);
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



void presets::expander_folder::set_variables(std::shared_ptr<variables> vars){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<list_folder>> (*this) -> vars = vars;
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}


#endif // presets_cpp