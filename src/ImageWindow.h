#pragma once

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/drawingarea.h>

namespace custom {

class Image : public Gtk::DrawingArea {
public:
  Image();
  ~Image() override = default;

  void load_image(const std::string& filepath);
  void force_redraw();

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

  void scale_pixmap();
  bool allocation_changed();

  Glib::RefPtr<Gdk::Pixbuf> m_pixbuf_scaled;
  Glib::RefPtr<Gdk::Pixbuf> m_pixbuf_full;

  bool m_previous_allocation = false;
  int m_previous_allocation_x;
  int m_previous_allocation_y;
};

class ImageWindow : public Gtk::Window {
public:
  ImageWindow();
  ~ImageWindow() override = default;

protected:
  void configure_widgets();
  void layout_widgets();

  Gtk::Box m_main_box;
  Image m_image;
  Gtk::Box m_controls_box;
  Gtk::Entry m_file_entry;
  Gtk::Button m_load_button;
};

}
