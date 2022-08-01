#ifndef list_operator_cpp
#define list_operator_cpp

#include "list_operator.hpp"

list_operator::list_operator(Glib::RefPtr<Gtk::Builder> b, std::string label_name, std::string label_name_store): 
	Glib::RefPtr<Gtk::TreeView>(Glib::RefPtr<Gtk::TreeView>::cast_dynamic(b -> get_object(label_name))), 
	Glib::RefPtr<Gtk::ListStore>(Glib::RefPtr<Gtk::ListStore>::cast_dynamic(b -> get_object(label_name_store))) {
	// if(!(b)) printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	// if(!(static_cast<Glib::RefPtr<Gtk::ListStore>>(*this))) printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	// if(!(Glib::RefPtr<Gtk::TreeView>::cast_dynamic(b -> get_object(label_name)))) printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



void list_operator::set_column_types(const Gtk::TreeModel::ColumnRecord& columns){
	// if(!(static_cast<Glib::RefPtr<Gtk::ListStore>>(*this))) printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> set_column_types(columns);
	// if(!(static_cast<Glib::RefPtr<Gtk::ListStore>>(*this))) printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



void list_operator::clear(){
	// if(!(static_cast<Glib::RefPtr<Gtk::ListStore>>(*this))) printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> clear();
	// if(!(static_cast<Glib::RefPtr<Gtk::ListStore>>(*this))) printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}




Gtk::TreeModel::iterator list_operator::add_row(){
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	// if(!(static_cast<Glib::RefPtr<Gtk::ListStore>>(*this))) printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	return *(static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> append());
	}



Gtk::TreeModel::Children list_operator::children(){
	return static_cast<Glib::RefPtr<Gtk::ListStore>>(*this) -> children();
	}



void list_operator::set_model(const Glib::RefPtr<Gtk::TreeModel>& model){
	static_cast<Glib::RefPtr<Gtk::TreeView>>(*this) -> set_model(model);
	}



template<typename ColumnType>
int list_operator::append_column(const Glib::ustring& title, 
		const Gtk::TreeModelColumn<ColumnType>& model_column){
	return static_cast<Glib::RefPtr<Gtk::TreeView>>(*this) -> append_column(title, model_column);
	}



template<>
int list_operator::append_column(const Glib::ustring& title, 
		const Gtk::TreeModelColumn<Glib::ustring>& model_column){
	return static_cast<Glib::RefPtr<Gtk::TreeView>>(*this) -> append_column(title, model_column);
	}



// template<>
// int list_operator::append_column(const Glib::ustring& title, 
// 		const Gtk::TreeModelColumn<Glib::ustring>& model_column){
// 	return append_column<Glib::ustring>(title, model_column);
// 	}

#endif // list_operator_cpp