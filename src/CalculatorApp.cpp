#include <iostream>
#include "CalculatorApp.h"

calc::CalculatorApp::CalculatorApp() {
  set_title("Calculator");
  set_border_width(12);

  configure_widgets();
  layout_widgets();

  show_all_children();
}

void calc::CalculatorApp::configure_widgets() {
  primary_entry.set_editable(false);
  primary_entry.set_can_focus(false);

  button_0.set_label("0");
  button_0.signal_clicked().connect([&]() { on_digit_clicked('0'); });
  button_1.set_label("1");
  button_1.signal_clicked().connect([&]() { on_digit_clicked('1'); });
  button_2.set_label("2");
  button_2.signal_clicked().connect([&]() { on_digit_clicked('2'); });
  button_3.set_label("3");
  button_3.signal_clicked().connect([&]() { on_digit_clicked('3'); });
  button_4.set_label("4");
  button_4.signal_clicked().connect([&]() { on_digit_clicked('4'); });
  button_5.set_label("5");
  button_5.signal_clicked().connect([&]() { on_digit_clicked('5'); });
  button_6.set_label("6");
  button_6.signal_clicked().connect([&]() { on_digit_clicked('6'); });
  button_7.set_label("7");
  button_7.signal_clicked().connect([&]() { on_digit_clicked('7'); });
  button_8.set_label("8");
  button_8.signal_clicked().connect([&]() { on_digit_clicked('8'); });
  button_9.set_label("9");
  button_9.signal_clicked().connect([&]() { on_digit_clicked('9'); });

  button_dot.set_label(".");
  button_dot.signal_clicked().connect([&]() { on_digit_clicked('.'); });

  button_plus.set_label("+");
  button_plus.signal_clicked().connect([&]() { on_operation_clicked(CalcOp::Plus); });
  button_minus.set_label("-");
  button_minus.signal_clicked().connect([&]() { on_operation_clicked(CalcOp::Minus); });
  button_mul.set_label("*");
  button_mul.signal_clicked().connect([&]() { on_operation_clicked(CalcOp::Mul); });
  button_div.set_label("%");
  button_div.signal_clicked().connect([&]() { on_operation_clicked(CalcOp::Div); });

  button_eql.set_label("=");
  button_eql.signal_clicked().connect([&]() { on_equal_clicked(); });
  button_clear.set_label("Cls");
  button_clear.signal_clicked().connect([&]() { on_clear_clicked(); });
}

void calc::CalculatorApp::layout_widgets() {
  add(grid);
  grid.set_row_spacing(6);
  grid.set_column_spacing(6);

  grid.attach(primary_entry, 0, 0, 4, 1);

  grid.attach(button_plus, 0, 1, 1, 1);
  grid.attach(button_minus, 1, 1, 1, 1);
  grid.attach(button_mul, 2, 1, 1, 1);
  grid.attach(button_div, 3, 1, 1, 1);

  grid.attach(button_7, 0, 2, 1, 1);
  grid.attach(button_8, 1, 2, 1, 1);
  grid.attach(button_9, 2, 2, 1, 1);
  grid.attach(button_clear, 3, 2, 1, 1);

  grid.attach(button_4, 0, 3, 1, 1);
  grid.attach(button_5, 1, 3, 1, 1);
  grid.attach(button_6, 2, 3, 1, 1);

  grid.attach(button_1, 0, 4, 1, 1);
  grid.attach(button_2, 1, 4, 1, 1);
  grid.attach(button_3, 2, 4, 1, 1);
  grid.attach(button_eql, 3, 4, 1, 2);

  grid.attach(button_0, 1, 5, 1, 1);
  grid.attach(button_dot, 2, 5, 1, 1);
}

void calc::CalculatorApp::on_digit_clicked(char digit) {
  calc.add_digit(digit);
  primary_entry.set_text(calc.get_display_value());
}

void calc::CalculatorApp::on_operation_clicked(calc::CalcOp op) {
  calc.set_operation(op);
  calc.store_display_value();
  primary_entry.set_text(calc.get_display_value());
}

void calc::CalculatorApp::on_equal_clicked() {
  calc.calculate();
  primary_entry.set_text(calc.get_display_value());
}

void calc::CalculatorApp::on_clear_clicked() {
  calc.clear_display();
  calc.store_display_value();
  primary_entry.set_text(calc.get_display_value());
}
