#include <gtkmm.h>
#include "ImageWindow.h"
#include "DrawWindow.h"
#include "LoginWindow.h"
#include "calc/CalculatorView.h"

int main(int argc, char* argv[]) {
  Gtk::Main kit(argc, argv);
//  calc::CalculatorView app;
  custom::LoginWindow app;
//  custom::DrawWindow app;
  
//  custom::ImageWindow app;
  Gtk::Main::run(app);
  return EXIT_SUCCESS;
}
