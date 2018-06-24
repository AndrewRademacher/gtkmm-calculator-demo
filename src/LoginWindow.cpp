#include "LoginWindow.h"

custom::LoginWindow::LoginWindow() {
  set_title("Custom GTK Widgets");
  set_border_width(12);
  set_resizable(false);
  set_position(Gtk::WindowPosition::WIN_POS_CENTER);

  configure_widgets();
  layout_widgets();

  show_all_children();
}

void custom::LoginWindow::configure_widgets() {
  m_welcome_message.set_text("<span size='17000'>Welcome to GTK</span>");
  m_welcome_message.set_use_markup(true);
  m_username_message.set_text("Username: ");
  m_password_message.set_text("Password: ");
  m_password_entry.set_visibility(false);

  m_signin_button.set_label("Sign-In");
  m_signin_button.signal_clicked().connect([&]() { on_submit_button_clicked(); });
  m_cancel_button.set_label("Cancel");
  m_cancel_button.signal_clicked().connect([&]() { on_cancel_button_clicked(); });
}

void custom::LoginWindow::layout_widgets() {
  add(m_main_box);
  m_main_box.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
  m_main_box.set_spacing(6);

  m_main_box.pack_start(m_welcome_message);

  m_main_box.pack_start(m_form_grid);
  m_form_grid.set_row_spacing(6);
  m_form_grid.set_column_spacing(6);
  m_form_grid.attach(m_username_message, 0, 1, 1, 1);
  m_form_grid.attach(m_password_message, 0, 2, 1, 1);
  m_form_grid.attach(m_username_entry, 1, 1, 1, 1);
  m_form_grid.attach(m_password_entry, 1, 2, 1, 1);

  m_main_box.pack_start(m_button_box);
  m_button_box.set_spacing(6);
  m_button_box.pack_start(m_cancel_button, Gtk::PackOptions::PACK_SHRINK);
  m_button_box.pack_end(m_signin_button, Gtk::PackOptions::PACK_SHRINK);
}

void custom::LoginWindow::on_submit_button_clicked() {
  m_welcome_message.set_text("<span size='17000'>Signed In!</span>");
  m_welcome_message.set_use_markup(true);
}

void custom::LoginWindow::on_cancel_button_clicked() {
  m_welcome_message.set_text("<span size='17000'>Canceled!</span>");
  m_welcome_message.set_use_markup(true);
}
