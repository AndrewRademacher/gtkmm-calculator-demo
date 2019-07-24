cmake_minimum_required(VERSION 3.10)
project(gtkmm_calculator_test)

set(CMAKE_CXX_STANDARD 17)

if (APPLE)
    set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/opt/libffi/lib/pkgconfig")
endif ()

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})

set(PROJECT_FILES
        src/calc/CalculatorView.cpp
        src/calc/CalculatorView.h
        src/calc/CalculatorController.cpp
        src/calc/CalculatorController.h
        src/LoginWindow.cpp
        src/LoginWindow.h
        src/DrawWindow.cpp
        src/DrawWindow.h
        src/ImageWindow.cpp
        src/ImageWindow.h
        )

add_executable(calculator src/main.cpp ${PROJECT_FILES})
target_include_directories(calculator PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(calculator
        ${GTKMM_LIBRARIES})
