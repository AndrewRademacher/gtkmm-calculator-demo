#include <gtkmm.h>
#include "CalculatorApp.h"

int main(int argc, char* argv[]) {
  Gtk::Main kit(argc, argv);
  calc::CalculatorApp calcapp;
  Gtk::Main::run(calcapp);
  return EXIT_SUCCESS;
}