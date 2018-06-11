cmake_minimum_required(VERSION 3.10)
project(gtkmm_calculator_test)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(calculator src/main.cpp src/CalculatorView.cpp src/CalculatorView.h src/CalculatorController.cpp src/CalculatorController.h)
target_include_directories(calculator PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(calculator
        ${GTKMM_LIBRARIES})