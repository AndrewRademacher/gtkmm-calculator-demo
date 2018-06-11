#pragma once

#include <string>

namespace calc {

enum class CalcOp {
  Plus,
  Minus,
  Mul,
  Div
};

class CalculatorController {
public:
  CalculatorController();

  void add_digit(char digit);
  void clear_display();
  const std::string& get_display_value();

  void set_operation(CalcOp op);
  CalcOp get_operation();

  void calculate();
  double get_stored_value();
  void store_display_value();

private:
  std::string display_value;
  double stored_value;
  CalcOp operation;
};

}
