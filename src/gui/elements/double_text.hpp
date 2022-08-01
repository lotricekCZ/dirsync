#ifndef double_text_hpp
#define double_text_hpp

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/builder.h>
#include <string>

class double_text {
	public:
		double_text(Glib::RefPtr<Gtk::Builder> b, std::string label_key, std::string label_value);
		double_text() = default;
		virtual ~double_text() = default;
		void set_value(std::string label_value);
		void set_value(uint64_t label_value);
	protected:
		std::pair<Glib::RefPtr<Gtk::Label>, Glib::RefPtr<Gtk::Label>> display_label;
		//Member widgets:
	};

#endif // double_text_hpp