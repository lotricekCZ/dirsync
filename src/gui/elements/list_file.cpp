#ifndef list_file_cpp
#define list_file_cpp

#include "list_file.hpp"

list_file::list_file(Glib::RefPtr<Gtk::Builder>& b, std::string label_name, std::string label_name_store): 
	std::shared_ptr<list_operator>(new list_operator(b, label_name, label_name_store)),
	std::shared_ptr<file_column>(new file_column()) {
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<list_operator>> (*this) -> clear();
	static_cast<std::shared_ptr<list_operator>> (*this) 
		-> set_column_types(*static_cast<std::shared_ptr<file_column>>(*this));
	static_cast<std::shared_ptr<list_operator>> (*this) 
		-> set_column_types(*static_cast<std::shared_ptr<file_column>>(*this));
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<std::shared_ptr<list_operator>> (*this) 
		-> set_model(
			static_cast<Glib::RefPtr<Gtk::ListStore>>
				(*static_cast<std::shared_ptr<list_operator>>
					(*this))	
			);

	auto l_op = static_cast<std::shared_ptr<list_operator>> (*this); 
	auto fc = static_cast<std::shared_ptr<file_column>> (*this);
	auto on_toggle = [this, fc, l_op] (const Glib::ustring& path){
		auto iter = l_op -> get_iter(path);
		(*iter)[fc -> selected] = !(*iter)[fc -> selected];
		};


	Glib::RefPtr<Gtk::CellRendererToggle>::cast_dynamic(b -> get_object("select")) -> signal_toggled()
		.connect(on_toggle);
	}



void list_file::add(found_file& f){
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	// static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> append()
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	std::optional<Gtk::TreeModel::iterator> o;
	if(f.id == 0){
		o = (static_cast<std::shared_ptr<list_operator>>(*this) -> add_row());
		f.id = ++_id;
		(**o)[static_cast<std::shared_ptr<file_column>>(*this) -> selected] 
			= 0; // relevant only to those that are newly appended 
		(**o)[static_cast<std::shared_ptr<file_column>>(*this) -> id] 	
			= f.id;
		// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		} else {
			o = get_iter(f.id);
			// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
			}// means it never came through system
	auto filetypes = [f](){
		std::stringstream s("");
		for(auto i: f.occurences)
			s << i.second.extension().string() << " ";
		return s.str();
	};
	// auto name = [f](){
	// 	return f.get_filename().string().substr(0, f.get_significant());
	// };
	if(!o){
		printf("\n\n\nNO VALUE\n\n\n\n");
		return;
		}
	/*
	id
	selected
	name
	number
	filetypes
	color
	*/
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	(**o)[static_cast<std::shared_ptr<file_column>>(*this) -> name]
		= f.get_stem().string().substr(0, f.get_significant());
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	(**o)[static_cast<std::shared_ptr<file_column>>(*this) -> number]
		= (unsigned long)f.get_occurence_count();
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	(**o)[static_cast<std::shared_ptr<file_column>>(*this) -> filetypes]
		= filetypes();
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	(**o)[static_cast<std::shared_ptr<file_column>>(*this) -> color]
		= std::string("rgb(25, 10, 45)");
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



void list_file::remove(found_file& f){
	remove(f.id);
	}



void list_file::remove(uint32_t id){
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	if(id == 0) return; // invalid id
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	auto iter = get_iter(id);
	if(iter) static_cast<std::shared_ptr<list_operator>> (*this) -> erase(*iter);
	}



std::optional<Gtk::TreeModel::iterator> list_file::get_iter(uint32_t id){
	std::optional<Gtk::TreeModel::iterator> o;
	Gtk::TreeModel::Children children = static_cast<Glib::RefPtr<Gtk::ListStore>>
											(*static_cast<std::shared_ptr<list_operator>>
													(*this)) -> children();
	for(Gtk::TreeModel::iterator row = children.begin(); row != children.end(); ++row){
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		uint64_t item_id = (*row)[static_cast<std::shared_ptr<file_column>>(*this) -> id];
		if(item_id == id){
			o = row;
			break;
			}
		}
	return o;
	}

// void list_file::append() {
//     count++;

//     row = *(m_refTreeModel->append());
//     row[m_Columns.m_col_id] = count;
//     row[m_Columns.m_col_name] = todo_entry->get_text();
//     row[m_Columns.m_col_percentage] = m_HScale.get_value();
// }

#endif // list_file_cpp