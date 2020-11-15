cmake_minimum_required(VERSION 3.8.2)
cmake_policy(SET CMP0048 NEW)
project(clean-editor-qml VERSION 1.0.0 LANGUAGES C CXX)

###########################
# Dependencies

find_package(Qt6 COMPONENTS Core Gui Qml Quick QuickControls2 REQUIRED)

###########################
# Targets

# Only used to make qml files accessible in VS
file(GLOB_RECURSE QML_SRC "*.qml")
source_group("Qml Files" FILES ${QML_SRC})

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/line-numbers.cpp
  src/line-numbers.h
  src/qml-editor-model.cpp
  src/qml-editor-model.h
  resources.qrc
  ${QML_SRC}
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    src
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    clean-editor-lib
)

target_compile_features(${PROJECT_NAME}
  PUBLIC
    cxx_std_17
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
