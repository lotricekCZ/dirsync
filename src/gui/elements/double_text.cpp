#ifndef double_text_cpp
#define double_text_cpp

#include "double_text.hpp"

double_text::double_text(Glib::RefPtr<Gtk::Builder> b, std::string label_key, std::string label_value){
	if(!(Glib::RefPtr<Gtk::Label>::cast_dynamic(b -> get_object(label_value)))) printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	display_label = std::make_pair(Glib::RefPtr<Gtk::Label>::cast_dynamic(b -> get_object(label_key)),
								Glib::RefPtr<Gtk::Label>::cast_dynamic(b -> get_object(label_value)));
	}


void double_text::set_value(std::string label_value){
	display_label.second -> set_text(label_value);
	}



void double_text::set_value(uint64_t label_value){
	display_label.second -> set_text(std::to_string(label_value));
	}


#endif // double_text_cpp