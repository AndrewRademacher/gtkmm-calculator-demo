//
// Created by Andrew Rademacher on 6/10/18.
//

#pragma once

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include "Calculator.h"

namespace calc {

class CalculatorApp : public Gtk::Window {
public:
  CalculatorApp();
  ~CalculatorApp() override = default;

protected:
  // Init
  void configure_widgets();
  void layout_widgets();

  // Signal handlers
  void on_digit_clicked(char digit);
  void on_operation_clicked(CalcOp op);
  void on_equal_clicked();
  void on_clear_clicked();

  // Member Widgets
  Gtk::Grid grid;
  Gtk::Entry primary_entry;

  Gtk::Button button_0;
  Gtk::Button button_1;
  Gtk::Button button_2;
  Gtk::Button button_3;
  Gtk::Button button_4;
  Gtk::Button button_5;
  Gtk::Button button_6;
  Gtk::Button button_7;
  Gtk::Button button_8;
  Gtk::Button button_9;
  Gtk::Button button_dot;

  Gtk::Button button_plus;
  Gtk::Button button_minus;
  Gtk::Button button_mul;
  Gtk::Button button_div;

  Gtk::Button button_eql;
  Gtk::Button button_clear;

  // Member controllers
  Calculator calc;
};

}
