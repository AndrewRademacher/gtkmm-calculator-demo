#pragma once

#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/box.h>
#include <gtkmm/radiobuttongroup.h>
#include <gtkmm/radiobutton.h>

namespace custom {

enum class AreaDrawing {
  Flag,
  Curve,
  Shapes,
  Text
};

class Area : public Gtk::DrawingArea {
public:
  Area();
  ~Area() override = default;

  void set_drawing(AreaDrawing d);
  void force_redraw();

protected:
  bool on_draw(const Cairo::RefPtr<::Cairo::Context>& cr) override;

private:
  bool draw_simple_flag(const ::Cairo::RefPtr<::Cairo::Context>& cr);
  bool draw_curve(const ::Cairo::RefPtr<::Cairo::Context>& cr);
  bool draw_shapes(const ::Cairo::RefPtr<::Cairo::Context>& cr);
  bool draw_text(const ::Cairo::RefPtr<::Cairo::Context>& cr);

  void pango_draw_text(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

  AreaDrawing m_drawing;
};

class DrawWindow : public Gtk::Window {
public:
  DrawWindow();
  ~DrawWindow() override = default;

protected:
  void configure_widgets();
  void layout_widgets();

private:
  Gtk::Box m_main_box;
  Area m_area;

  Gtk::Box m_selection_box;
  Gtk::RadioButton m_flag_radio;
  Gtk::RadioButton m_curve_radio;
  Gtk::RadioButton m_shapes_radio;
  Gtk::RadioButton m_text_radio;
};

}
