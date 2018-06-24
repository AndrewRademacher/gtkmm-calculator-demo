#pragma once

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/box.h>

namespace custom {

class LoginWindow : public Gtk::Window {
public:
  LoginWindow();
  ~LoginWindow() override = default;

protected:
  void configure_widgets();
  void layout_widgets();

  void on_submit_button_clicked();
  void on_cancel_button_clicked();

  Gtk::Box m_main_box;
  Gtk::Grid m_form_grid;
  Gtk::Box m_button_box;
  Gtk::Label m_welcome_message;
  Gtk::Label m_username_message;
  Gtk::Label m_password_message;
  Gtk::Entry m_username_entry;
  Gtk::Entry m_password_entry;
  Gtk::Button m_signin_button;
  Gtk::Button m_cancel_button;
};

}
