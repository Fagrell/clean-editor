cmake_minimum_required(VERSION 3.8.2)
cmake_policy(SET CMP0048 NEW)
project(clean-editor-qml VERSION 1.0.0 LANGUAGES C CXX)

###########################
# Dependencies

find_package(Qt5 COMPONENTS Core Gui Qml Quick QuickControls2 REQUIRED)

###########################
# Targets

add_executable(${PROJECT_NAME}
  src/main.cpp
  views.qrc
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    src
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    clean-editor-lib
)

target_compile_options(${PROJECT_NAME}
  PUBLIC
    -Wall
    -Werror
)

target_compile_features(${PROJECT_NAME}
  PUBLIC
    cxx_std_11
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    AUTOMOC ON
    AUTORCC ON
)
