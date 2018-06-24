#include <gdkmm.h>
#include <iostream>
#include "ImageWindow.h"

custom::ImageWindow::ImageWindow() {
  set_title("Image Window");
  set_border_width(12);

  configure_widgets();
  layout_widgets();

  show_all_children();
}

void custom::ImageWindow::configure_widgets() {
  m_image.set_size_request(600, 600);

  m_file_entry.signal_activate().connect([&]() { m_image.load_image(m_file_entry.get_text()); });
  m_load_button.set_label("Load Image");
  m_load_button.signal_clicked().connect([&]() { m_image.load_image(m_file_entry.get_text()); });
}

void custom::ImageWindow::layout_widgets() {
  add(m_main_box);

  m_main_box.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
  m_main_box.set_spacing(6);
  m_main_box.pack_start(m_image, Gtk::PackOptions::PACK_EXPAND_WIDGET);
  m_main_box.pack_start(m_controls_box, Gtk::PackOptions::PACK_SHRINK);

  m_controls_box.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
  m_controls_box.set_spacing(6);
  m_controls_box.pack_start(m_file_entry, Gtk::PackOptions::PACK_EXPAND_WIDGET);
  m_controls_box.pack_end(m_load_button, Gtk::PackOptions::PACK_SHRINK);
}

bool custom::Image::allocation_changed() {
  const int width = get_allocation().get_width();
  const int height = get_allocation().get_height();

  if (m_previous_allocation) {
    if (width != m_previous_allocation_x || height != m_previous_allocation_y) {
      m_previous_allocation_x = width;
      m_previous_allocation_y = height;
      return true;
    } else {
      return false;
    }
  } else {
    m_previous_allocation = true;
    m_previous_allocation_x = width;
    m_previous_allocation_x = height;
    return true;
  }
}

bool custom::Image::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  if (m_pixbuf_full) {
    const int width = get_allocation().get_width();
    const int height = get_allocation().get_height();

    if (allocation_changed()) {
      scale_pixmap();
    }

    const int scaled_center_x = m_pixbuf_scaled->get_width() / 2;
    const int scaled_center_y = m_pixbuf_scaled->get_height() / 2;
    const int frame_center_x = width / 2;
    const int frame_center_y = height / 2;

    Gdk::Cairo::set_source_pixbuf(cr,
                                  m_pixbuf_scaled,
                                  frame_center_x - scaled_center_x,
                                  frame_center_y - scaled_center_y);
    cr->rectangle(0, 0, width, height);
    cr->fill();
  }

  return true;
}

void custom::Image::scale_pixmap() {
  const int width = get_allocation().get_width();
  const int height = get_allocation().get_height();

  const double ratio_x = static_cast<double>(width) / m_pixbuf_full->get_width();
  const double ratio_y = static_cast<double>(height) / m_pixbuf_full->get_height();
  const double ratio = std::__1::min(ratio_x, ratio_y);

  const auto dest_width = static_cast<int>(m_pixbuf_full->get_width() * ratio);
  const auto dest_height = static_cast<int>(m_pixbuf_full->get_height() * ratio);

  m_pixbuf_scaled = m_pixbuf_full->scale_simple(dest_width, dest_height, Gdk::INTERP_BILINEAR);
}

custom::Image::Image() {
  set_size_request(600, 600);
}

void custom::Image::load_image(const std::string& filepath) {
  m_pixbuf_full = Gdk::Pixbuf::create_from_file(filepath);
  m_pixbuf_scaled.clear();
  m_previous_allocation = false;
  force_redraw();
}

void custom::Image::force_redraw() {
  auto win = get_window();
  if (win) {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r, false);
  }
}
