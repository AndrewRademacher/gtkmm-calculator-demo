#include "DrawWindow.h"

custom::DrawWindow::DrawWindow() {
  set_title("Draw Window");

  configure_widgets();
  layout_widgets();

  show_all_children();
}

void custom::DrawWindow::configure_widgets() {
  m_flag_radio.set_label("Flag");
  m_flag_radio.signal_clicked().connect([&]() { m_area.set_drawing(AreaDrawing::Flag); });

  m_curve_radio.set_label("Curve");
  m_curve_radio.join_group(m_flag_radio);
  m_curve_radio.signal_clicked().connect([&]() { m_area.set_drawing(AreaDrawing::Curve); });

  m_shapes_radio.set_label("Shapes");
  m_shapes_radio.join_group(m_flag_radio);
  m_shapes_radio.signal_clicked().connect([&]() { m_area.set_drawing(AreaDrawing::Shapes); });

  m_text_radio.set_label("Text");
  m_text_radio.join_group(m_flag_radio);
  m_text_radio.signal_clicked().connect([&]() { m_area.set_drawing(AreaDrawing::Text); });
}

void custom::DrawWindow::layout_widgets() {
  add(m_main_box);
  m_main_box.set_spacing(6);
  m_main_box.pack_start(m_area);
  m_main_box.pack_start(m_selection_box);

  m_selection_box.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
  m_selection_box.set_spacing(6);
  m_selection_box.pack_start(m_flag_radio, Gtk::PackOptions::PACK_SHRINK);
  m_selection_box.pack_start(m_curve_radio, Gtk::PackOptions::PACK_SHRINK);
  m_selection_box.pack_start(m_shapes_radio, Gtk::PackOptions::PACK_SHRINK);
  m_selection_box.pack_start(m_text_radio, Gtk::PackOptions::PACK_SHRINK);
}

bool custom::Area::on_draw(const ::Cairo::RefPtr<::Cairo::Context>& cr) {
  switch (m_drawing) {
  case AreaDrawing::Flag: return draw_simple_flag(cr);
  case AreaDrawing::Curve: return draw_curve(cr);
  case AreaDrawing::Shapes: return draw_shapes(cr);
  case AreaDrawing::Text: return draw_text(cr);
  }
}

custom::Area::Area() : m_drawing(AreaDrawing::Flag) {
  set_size_request(400, 400);
}

bool custom::Area::draw_simple_flag(const ::Cairo::RefPtr<::Cairo::Context>& cr) {
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  const int xc = width / 2;
  const int yc = height / 2;

  cr->set_line_width(10.0);

  cr->set_source_rgb(0.8, 0.0, 0.0);
  cr->move_to(0, 0);
  cr->line_to(xc, yc);
  cr->line_to(0, height);
  cr->move_to(xc, yc);
  cr->line_to(width, yc);
  cr->stroke();

  return true;
}

bool custom::Area::draw_curve(const ::Cairo::RefPtr<::Cairo::Context>& cr) {
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  double x0 = 0.1, y0 = 0.5; // start point
  double x1 = 0.4, y1 = 0.9; // control point 1
  double x2 = 0.6, y2 = 0.1; // control point 2
  double x3 = 0.9, y3 = 0.5;

  // scale to unit square (0 to 1 width and height)
  cr->scale(width, height);

  cr->set_line_width(0.05);
  //draw curve
  cr->move_to(x0, y0);
  cr->curve_to(x1, y1, x2, y2, x3, y3);
  cr->stroke();

  //show control points
  cr->set_source_rgba(1, 0.2, 0.2, 0.6);
  cr->move_to(x0, y0);
  cr->line_to(x1, y1);
  cr->move_to(x2, y2);
  cr->line_to(x3, y3);
  cr->stroke();

  return true;
}

void custom::Area::set_drawing(custom::AreaDrawing d) {
  m_drawing = d;
  force_redraw();
}

void custom::Area::force_redraw() {
  auto win = get_window();
  if (win) {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r, false);
  }
}

bool custom::Area::draw_shapes(const ::Cairo::RefPtr<::Cairo::Context>& cr) {
  const int width = get_allocation().get_width();
  const int height = get_allocation().get_height();
  const int lesser = std::min(width, height);

  const int xc = width / 2;
  const int yc = height / 2;

  cr->set_line_width(lesser * 0.02); // outline thickness changes with window size.

  // first draw a simple unclosed arc
  cr->save();
  cr->arc(width / 3.0, height / 4.0, lesser / 4.0, -(M_PI / 5.0), M_PI);
  cr->close_path(); // line back to start point
  cr->set_source_rgb(0.0, 0.8, 0.0);
  cr->fill_preserve();
  cr->restore(); // back to opaque black
  cr->stroke(); // outline it

  // now draw a circle
  cr->save();
  cr->arc(xc, yc, lesser / 4.0, 0.0, 2.0 * M_PI); // full circle
  cr->set_source_rgba(0.0, 0.0, 0.8, 0.6); // partially translucent
  cr->fill_preserve();
  cr->restore();
  cr->stroke();

  // finally an ellipse
  const double ex = xc;
  const double ey = 3.0 * height / 4.0;
  const double ew = 3.0 * width / 4.0;
  const double eh = height / 3.0;

  cr->save();
  cr->translate(ex, ey);
  cr->scale(ew / 2.0, eh / 2.0); // for width: ew / 2.0 == 1.0
  // for heigh: eh / 2.0 == 1.0
  cr->arc(0.0, 0.0, 1.0, 0.0, 2 * M_PI); // circle centered at (0, 0) with radius of 1.0
  cr->set_source_rgba(0.8, 0.0, 0.0, 0.7);
  cr->fill_preserve();
  cr->restore();
  cr->stroke();

  return true;
}

bool custom::Area::draw_text(const ::Cairo::RefPtr<::Cairo::Context>& cr) {
  const int width = get_allocation().get_width();
  const int height = get_allocation().get_height();

  const int rectangle_width = width;
  const int rectangle_height = height / 2;

  // Draw black rectangle
  cr->set_source_rgb(0, 0, 0);
  cr->rectangle(0, 0, rectangle_width, rectangle_height);
  cr->fill();

  // Draw white text
  cr->set_source_rgb(1, 1, 1);
  pango_draw_text(cr, rectangle_width, rectangle_height);

  // flip image vertically
  Cairo::Matrix matrix(1.0, 0.0, 0.0, -1.0, 0.0, height);
  cr->transform(matrix);

  // Draw white rectangle
  cr->set_source_rgb(1, 1, 1);
  cr->rectangle(0, 0, rectangle_width, rectangle_height);
  cr->fill();

  // Draw black text
  cr->set_source_rgb(0, 0, 0);
  pango_draw_text(cr, rectangle_width, rectangle_height);

  return true;
}

void custom::Area::pango_draw_text(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
  Pango::FontDescription font;
  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_BOLD);

  auto layout = create_pango_layout("Hi there!");
  layout->set_font_description(font);

  int text_width;
  int text_height;

  layout->get_pixel_size(text_width, text_height);

  cr->move_to(static_cast<double>(width - text_width) / 2, static_cast<double>(height - text_height) / 2);
  layout->show_in_cairo_context(cr);
}
