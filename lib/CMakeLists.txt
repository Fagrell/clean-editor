cmake_minimum_required(VERSION 3.8.2)
cmake_policy(SET CMP0048 NEW)
project(clean-editor-lib VERSION 1.0.0 LANGUAGES C CXX)

###########################
# Dependencies
find_package(Qt5 COMPONENTS Core REQUIRED)

###########################
# Targets
add_library(${PROJECT_NAME} SHARED
  src/main-controller.cpp
  src/file-handler.cpp
  src/document-handler.cpp
  src/documents-model.cpp

  public/main-controller.h
  public/globals.h
  public/file-handler.h
  public/document-handler.h
  public/documents-model.h
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:public>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE
    QML_EDITOR_LIBRARY
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    Qt5::Core
)

target_compile_features(${PROJECT_NAME}
  PUBLIC
    cxx_std_14
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    AUTOMOC ON
)

###########################
# Include tests

add_subdirectory(tests)
