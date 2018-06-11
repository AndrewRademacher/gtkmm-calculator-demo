#include <sstream>
#include "CalculatorController.h"

calc::CalculatorController::CalculatorController()
    : display_value(""), stored_value(0), operation(CalcOp::Plus) {}

void calc::CalculatorController::add_digit(char digit) {
  if (digit == '.') {
    if (!std::count(display_value.begin(), display_value.end(), '.')) {
      display_value.push_back('.');
    }
  } else {
    display_value.push_back(digit);
  }
}

void calc::CalculatorController::clear_display() {
  display_value.clear();
}

const std::string& calc::CalculatorController::get_display_value() {
  return display_value;
}

void calc::CalculatorController::set_operation(calc::CalcOp op) {
  operation = op;
}

calc::CalcOp calc::CalculatorController::get_operation() {
  return operation;
}

void calc::CalculatorController::calculate() {
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

double calc::CalculatorController::get_stored_value() {
  return stored_value;
}

void calc::CalculatorController::store_display_value() {
  char* end;
  stored_value = display_value.empty() ? 0 : std::strtod(display_value.data(), &end);
  display_value = "";
}
