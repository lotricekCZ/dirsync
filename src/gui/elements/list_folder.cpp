#ifndef list_folder_cpp
#define list_folder_cpp

#include "list_folder.hpp"

list_folder::list_folder(Glib::RefPtr<Gtk::Builder>& b, std::string label_name, std::string label_name_store): 
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



void list_folder::add(std::filesystem::path& f){
	// static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> append()
	Gtk::TreeModel::iterator o 
		= (static_cast<std::shared_ptr<list_operator>>(*this) -> add_row());
	(*o)[static_cast<std::shared_ptr<folder_column>>(*this) -> selected] 
		= 0;
	(*o)[static_cast<std::shared_ptr<folder_column>>(*this) -> name]
		= f.string();
	}



std::optional<Gtk::TreeModel::iterator> list_folder::add(){
	// static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> append()
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	if(edited){ // means that editing has finished
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		std::vector<std::filesystem::path> p;
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		auto o = static_cast<Glib::RefPtr<Gtk::ListStore>>
					(*static_cast<std::shared_ptr<list_operator>>
							(*this)) -> children();
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		Glib::ustring s;
		for(Gtk::TreeModel::iterator row = o.begin(); row != o.end(); ++row){
			s = ((*row)[static_cast<std::shared_ptr<folder_column>>(*this) -> name]);
			if(std::filesystem::exists(std::filesystem::path(s.c_str())))
				p.emplace_back(s.c_str());
				}
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		((o)[o.size() - 1])[static_cast<std::shared_ptr<folder_column>>(*this) -> editable] 
			= edited  
			= 0;
		if(vars -> insert_directory(p)) { // if the new entry is valid
			return ((o)[o.size() - 1]);
			}
		static_cast<std::shared_ptr<list_operator>> (*this) -> erase(((o)[o.size() - 1]));
		return std::nullopt;

		} else {
			printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
			Gtk::TreeModel::iterator o 
				= (static_cast<std::shared_ptr<list_operator>>(*this) -> add_row());
			(*o)[static_cast<std::shared_ptr<folder_column>>(*this) -> selected] 
				= 0;
			(*o)[static_cast<std::shared_ptr<folder_column>>(*this) -> editable] 
				= edited  
				= 1;
			printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
			return o;
			}
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



void list_folder::clear(){
	static_cast<std::shared_ptr<list_operator>> (*this) -> clear();
	}



void list_folder::start(){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	printf(": %i\n", vars -> get_directories().size());
	
	for(auto i: vars -> get_directories()){
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		Gtk::TreeModel::iterator o 
				= (static_cast<std::shared_ptr<list_operator>>(*this) -> add_row());
		(*o)[static_cast<std::shared_ptr<folder_column>>(*this) -> selected] 
			= 0;
		(*o)[static_cast<std::shared_ptr<folder_column>>(*this) -> editable] 
			= edited  
			= 0;
		(*o)[static_cast<std::shared_ptr<folder_column>>(*this) -> name] 
			= i.string();
		}
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



void list_folder::print(){
	std::vector<std::filesystem::path> p;
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	auto o = static_cast<Glib::RefPtr<Gtk::ListStore>>
				(*static_cast<std::shared_ptr<list_operator>>
						(*this)) -> children();
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	printf("\n\n\n\n\n\n");
	Glib::ustring s;
	for(Gtk::TreeModel::iterator row = o.begin(); row != o.end(); ++row){
		s = ((*row)[static_cast<std::shared_ptr<folder_column>>(*this) -> name]);
		printf("%s\n", s.c_str());
		}
	printf("\n\n\n\n\n\n");
	}



void list_folder::clear_selected(){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	std::vector<std::filesystem::path> removed;
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
				printf("%s: %i %i\n", __PRETTY_FUNCTION__, children.size(), __LINE__);
				Glib::ustring us = (*row)[static_cast<std::shared_ptr<folder_column>>(*this) -> name];
				printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
				row = static_cast<std::shared_ptr<list_operator>> (*this) -> erase(row);
				if(us.size()) removed.emplace_back(us.c_str());
				if(row == children.end()) { // last element removed, nothing to edit
					edited = false;
					break;
					}
				// row = children.begin();
				}
			}
		}
	for(auto a: removed)
		printf("removing %s\n", a.c_str());
	vars -> remove_directory(removed);
	}



std::vector<bool> list_folder::get_checked(){
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

#endif // list_folder_cpp