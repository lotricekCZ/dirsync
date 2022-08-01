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
	// static_cast<std::shared_ptr<list_operator>> (*this) 
	// 	-> append_column(Glib::ustring("name"), static_cast<std::shared_ptr<file_column>>(*this) -> name);
	// static_cast<Glib::RefPtr<Gtk::TreeView>>
	// 	(*static_cast<std::shared_ptr<list_operator>>
	// 		(*this)) -> set_headers_visible(1);
	}



void list_file::add(found_file& f){
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	// static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> append()
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	std::optional<Gtk::TreeModel::iterator> o;
	if(f.id == 0){
		o = (static_cast<std::shared_ptr<list_operator>>(*this) -> add_row());
		f.id = ++_id;
		(**o)[static_cast<std::shared_ptr<file_column>>(*this) -> selected] = 0; // relevant only to those that are newly appended 
		(**o)[static_cast<std::shared_ptr<file_column>>(*this) -> id] 		= f.id;
		printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		} else {
			// *this)
			Gtk::TreeModel::Children children = static_cast<Glib::RefPtr<Gtk::ListStore>>
													(*static_cast<std::shared_ptr<list_operator>>
															(*this)) -> children();
			for(Gtk::TreeModel::iterator row = children.begin(); row != children.end(); ++row){
				printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
				uint64_t item_id = 5;
				Gtk::TreeModel::Children elements = row -> children();
				// Glib::ustring item_nm("");
				// Gtk::TreeModelColumn<uint64_t> t = *elements[0];
				printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
				item_id = (*row)[static_cast<std::shared_ptr<file_column>>(*this) -> id];
				Glib::ustring item_nm = (*row)[static_cast<std::shared_ptr<file_column>>(*this) -> name];
				Glib::ustring item_ft = (*row)[static_cast<std::shared_ptr<file_column>>(*this) -> filetypes];
				printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
				// row -> get_value(columns::name, item_nm);
				printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
				printf("value: %s\t%s\t%i\n", item_nm.c_str(), item_ft.c_str(), item_id);
				// printf("value: %s\n", item_ft.c_str());
				// printf("value: %s\n", item_nm.c_str());
				// printf("value: %i\n", item_id);
				if(item_id ==  f.id){
					printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
					o = row;
					printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
					break;
					}
				}
				printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
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
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);

	// o[static_cast<std::shared_ptr<file_column>>(*this) -> number] = 666;
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	// static_cast<Glib::RefPtr<Gtk::TreeView>>
	// 	(*static_cast<std::shared_ptr<list_operator>>
	// 		(*this)) -> show();
	}

// void list_file::append() {
//     count++;

//     row = *(m_refTreeModel->append());
//     row[m_Columns.m_col_id] = count;
//     row[m_Columns.m_col_name] = todo_entry->get_text();
//     row[m_Columns.m_col_percentage] = m_HScale.get_value();
// }

#endif // list_file_cpp