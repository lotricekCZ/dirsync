#ifndef list_folder_cpp
#define list_folder_cpp

#include "list_folder.hpp"

list_folder::list_folder(Glib::RefPtr<Gtk::Builder>& b, std::string label_name, std::string label_name_store): 
	std::shared_ptr<list_operator>(new list_operator(b, label_name, label_name_store)) {
	// this -> list_operator::Glib::RefPtr	<Gtk::ListStore>
	// this -> list_operator::set_column_types(static_cast<file_column>(*this));
	}

void list_folder::add(found_file& f){
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	// static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> append()
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	Gtk::TreeModel::iterator o;
	if(f.id == 0){
		o = (static_cast<std::shared_ptr<list_operator>>(*this) -> add_row());
		f.id = _id++;
		} else {
			auto children = (static_cast<std::shared_ptr<list_operator>>(*this) -> children());
			for(auto i = children.begin(); i != children.end(); i++){
				uint64_t item_id;
				i -> get_value(columns::id, item_id);
				if(item_id ==  f.id){
					o = *i;
					break;
					}
				}
			}// means it never came through system
		
	o -> set_value(columns::id, 					666);
	o -> set_value(columns::selected,				1);
	o -> set_value(columns::name,					std::string("chleba"));
	o -> set_value(columns::number_of_occurences, 	666);
	o -> set_value(columns::filetypes,				std::string("number"));
	o -> set_value(columns::color,					666);

	// o[static_cast<std::shared_ptr<file_column>>(*this) -> number] = 666;
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}

// void list_folder::append() {
//     count++;

//     row = *(m_refTreeModel->append());
//     row[m_Columns.m_col_id] = count;
//     row[m_Columns.m_col_name] = todo_entry->get_text();
//     row[m_Columns.m_col_percentage] = m_HScale.get_value();
// }

#endif // list_folder_cpp