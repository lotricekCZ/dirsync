#ifndef window_hpp
#define window_hpp

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class window: public Gtk::Window {

public:
	window();
	virtual ~window();

protected:
	//Signal handlers:
	void on_button_clicked();

	//Member widgets:
	Glib::RefPtr<Gtk::Label> display_label;
	Glib::RefPtr<Gtk::Button> display_btn;
	Glib::RefPtr<Gtk::Builder> ui;
	Gtk::Button m_button;
};

#endif // window_hpp