#include <gtkmm.h>
#include "CalculatorView.h"

int main(int argc, char* argv[]) {
  Gtk::Main kit(argc, argv);
  calc::CalculatorView calcapp;
  Gtk::Main::run(calcapp);
  return EXIT_SUCCESS;
}