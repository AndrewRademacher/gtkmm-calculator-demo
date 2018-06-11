#include <sstream>
#include "Calculator.h"

calc::Calculator::Calculator()
    : display_value(""), stored_value(0), operation(CalcOp::Plus) {}

void calc::Calculator::add_digit(char digit) {
  if (digit == '.') {
    if (!std::count(display_value.begin(), display_value.end(), '.')) {
      display_value.push_back('.');
    }
  } else {
    display_value.push_back(digit);
  }
}

void calc::Calculator::clear_display() {
  display_value.clear();
}

const std::string& calc::Calculator::get_display_value() {
  return display_value;
}

void calc::Calculator::set_operation(calc::CalcOp op) {
  operation = op;
}

calc::CalcOp calc::Calculator::get_operation() {
  return operation;
}

void calc::Calculator::calculate() {
  char* end;
  double input = std::strtod(display_value.data(), &end);
  switch (operation) {
  case CalcOp::Plus: stored_value = stored_value + input;
    break;
  case CalcOp::Minus: stored_value = stored_value - input;
    break;
  case CalcOp::Mul: stored_value = stored_value * input;
    break;
  case CalcOp::Div: stored_value = stored_value / input;
    break;
  }

  std::stringstream ss;
  ss << stored_value;
  display_value = ss.str();
}

double calc::Calculator::get_stored_value() {
  return stored_value;
}

void calc::Calculator::store_display_value() {
  char* end;
  stored_value = display_value.empty() ? 0 : std::strtod(display_value.data(), &end);
  display_value = "";
}
