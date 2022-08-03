#ifndef list_blacklist_cpp
#define list_blacklist_cpp

#include "list_blacklist.hpp"

list_blacklist::list_blacklist(Glib::RefPtr<Gtk::Builder>& b, std::string label_name, std::string label_name_store): 
	std::shared_ptr<list_operator>(new list_operator(b, label_name, label_name_store)),
	std::shared_ptr<folder_column>(new folder_column()) {
	
	static_cast<std::shared_ptr<list_operator>> (*this) -> clear();
	static_cast<std::shared_ptr<list_operator>> (*this) 
		-> set_column_types(*static_cast<std::shared_ptr<folder_column>>(*this));
	static_cast<std::shared_ptr<list_operator>> (*this) 
		-> set_model(
			static_cast<Glib::RefPtr<Gtk::ListStore>>
				(*static_cast<std::shared_ptr<list_operator>>
					(*this))	
			);
	auto l_op = static_cast<std::shared_ptr<list_operator>> (*this); 
	auto fc = static_cast<std::shared_ptr<folder_column>> (*this);
	auto on_toggle = [this, fc, l_op, b] (const Glib::ustring& path){
		auto iter = l_op -> get_iter(path);
		(*iter)[fc -> selected] = !(*iter)[fc -> selected];
		};

	Glib::RefPtr<Gtk::CellRendererToggle>::cast_dynamic(b -> get_object("folder_select")) -> signal_toggled()
		.connect(on_toggle);
	}



void list_blacklist::add(std::filesystem::path& f){
	// static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> append()
	Gtk::TreeModel::iterator o 
		= (static_cast<std::shared_ptr<list_operator>>(*this) -> add_row());
	(*o)[static_cast<std::shared_ptr<folder_column>>(*this) -> selected] 
		= 0;
	(*o)[static_cast<std::shared_ptr<folder_column>>(*this) -> name]
		= f.string();
	}



Gtk::TreeModel::iterator list_blacklist::add(){
	// static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> append()
	if(edited){
		std::vector<std::filesystem::path> p;
		auto o = static_cast<Glib::RefPtr<Gtk::ListStore>>
					(*static_cast<std::shared_ptr<list_operator>>
							(*this)) -> children();

		Glib::ustring s;
		for(Gtk::TreeModel::iterator row = o.begin(); row != o.end(); ++row){
			s = ((*row)[static_cast<std::shared_ptr<folder_column>>(*this) -> name]);
			if(std::filesystem::exists(std::filesystem::path(s.c_str())))
				p.emplace_back(s.c_str());
			}
		
		vars -> insert_directory(p);
		}
	Gtk::TreeModel::iterator o 
		= (static_cast<std::shared_ptr<list_operator>>(*this) -> add_row());
	(*o)[static_cast<std::shared_ptr<folder_column>>(*this) -> selected] 
		= 0;
	(*o)[static_cast<std::shared_ptr<folder_column>>(*this) -> editable] 
		= edited  
		= 1;
	
	}



void list_blacklist::clear(){
	static_cast<std::shared_ptr<list_operator>> (*this) -> clear(); 
	}



void list_blacklist::clear_selected(){
	auto selected = get_checked();
	auto total = vars -> get_blacklist();
	static_cast<std::shared_ptr<list_operator>> (*this) -> clear(); 
	}



std::vector<bool> list_blacklist::get_checked(){
	// static_cast<std::shared_ptr<list_operator>> (*this) -> clear();
	std::vector<bool> ret;
	Gtk::TreeModel::Children children = static_cast<Glib::RefPtr<Gtk::ListStore>>
											(*static_cast<std::shared_ptr<list_operator>>
													(*this)) -> children();
	for(Gtk::TreeModel::iterator row = children.begin(); row != children.end(); ++row){
		ret.push_back((*row)[static_cast<std::shared_ptr<folder_column>>(*this) -> selected]);
		}
	return ret;
	}

#endif // list_blacklist_cpp