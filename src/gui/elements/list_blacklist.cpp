#ifndef list_blacklist_cpp
#define list_blacklist_cpp

#include "list_blacklist.hpp"

list_blacklist::list_blacklist(Glib::RefPtr<Gtk::Builder>& b, std::string label_name, std::string label_name_store): 
	std::shared_ptr<list_operator>(new list_operator(b, label_name, label_name_store)),
	std::shared_ptr<blacklist_column>(new blacklist_column()) {
	
	static_cast<std::shared_ptr<list_operator>> (*this) -> clear();
	static_cast<std::shared_ptr<list_operator>> (*this) 
		-> set_column_types(*static_cast<std::shared_ptr<blacklist_column>>(*this));
	static_cast<std::shared_ptr<list_operator>> (*this) 
		-> set_model(
			static_cast<Glib::RefPtr<Gtk::ListStore>>
				(*static_cast<std::shared_ptr<list_operator>>
					(*this))	
			);
	auto l_op = static_cast<std::shared_ptr<list_operator>> (*this); 
	auto fc = static_cast<std::shared_ptr<blacklist_column>> (*this);
	auto on_toggle = [this, fc, l_op, b] (const Glib::ustring& path){
		auto iter = l_op -> get_iter(path);
		(*iter)[fc -> selected] = !(*iter)[fc -> selected];
		};

	Glib::RefPtr<Gtk::CellRendererToggle>::cast_dynamic(b -> get_object("blacklist_select")) -> signal_toggled()
		.connect(on_toggle);
	}



void list_blacklist::add(std::string& f){
	// static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> append()
	Gtk::TreeModel::iterator o 
		= (static_cast<std::shared_ptr<list_operator>>(*this) -> add_row());
	(*o)[static_cast<std::shared_ptr<blacklist_column>>(*this) -> selected] 
		= 0;
	(*o)[static_cast<std::shared_ptr<blacklist_column>>(*this) -> name]
		= f;
	}



Gtk::TreeModel::iterator list_blacklist::add(){
	// static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> append()
	if(edited){
		std::vector<std::string> p;
		auto o = static_cast<Glib::RefPtr<Gtk::ListStore>>
					(*static_cast<std::shared_ptr<list_operator>>
							(*this)) -> children();

		Glib::ustring s;
		for(Gtk::TreeModel::iterator row = o.begin(); row != o.end(); ++row){
			s = ((*row)[static_cast<std::shared_ptr<blacklist_column>>(*this) -> name]);
			std::string ext(s.c_str());
			if(ext.size() && s.find('.') == 0)
				p.emplace_back(s.c_str());
			}
		
		vars -> insert_blacklist(p);
		}
	Gtk::TreeModel::iterator o 
		= (static_cast<std::shared_ptr<list_operator>>(*this) -> add_row());
	(*o)[static_cast<std::shared_ptr<blacklist_column>>(*this) -> selected] 
		= 0;
	(*o)[static_cast<std::shared_ptr<blacklist_column>>(*this) -> editable] 
		= edited  
		= 1;
	
	}



void list_blacklist::clear(){
	static_cast<std::shared_ptr<list_operator>> (*this) -> clear(); 
	}



void list_blacklist::start(){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	printf(": %i\n", vars -> get_blacklist().size());
	
	for(auto i: vars -> get_blacklist()){
		add(i);
		}
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



void list_blacklist::clear_selected(){
	// auto selected = get_checked();
	// auto total = vars -> get_blacklist();
	// static_cast<std::shared_ptr<list_operator>> (*this) -> clear();

	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	std::vector<std::string> removed;
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	// auto total = vars -> get_directories();
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	Gtk::TreeModel::Children children = static_cast<Glib::RefPtr<Gtk::ListStore>>
											(*static_cast<std::shared_ptr<list_operator>>
													(*this)) -> children();
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	uint32_t i = 0;
	bool erased = 0;
	if(children.size()){
		auto selected = get_checked();
		for(Gtk::TreeModel::iterator row = children.begin(); row != children.end(); (erased? row: row++)){
			erased = false;
			if(selected.at(i++)){
				erased = true;
				printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
				Glib::ustring us = (*row)[static_cast<std::shared_ptr<blacklist_column>>(*this) -> name];
				printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
				row = static_cast<std::shared_ptr<list_operator>> (*this) -> erase(row);
				if(us.size()) removed.emplace_back(us.c_str());
				if(row == children.end()) { // last element removed, nothing to edit
					edited = false;
					break;
					}
				}
			}
		}
	for(auto a: removed)
		printf("removing %s\n", a.c_str());
	vars -> remove_blacklist(removed);

	}



std::vector<bool> list_blacklist::get_checked(){
	// static_cast<std::shared_ptr<list_operator>> (*this) -> clear();
	std::vector<bool> ret;
	Gtk::TreeModel::Children children = static_cast<Glib::RefPtr<Gtk::ListStore>>
											(*static_cast<std::shared_ptr<list_operator>>
													(*this)) -> children();
	for(Gtk::TreeModel::iterator row = children.begin(); row != children.end(); ++row){
		ret.push_back((*row)[static_cast<std::shared_ptr<blacklist_column>>(*this) -> selected]);
		}
	return ret;
	}

#endif // list_blacklist_cpp