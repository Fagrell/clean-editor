cmake_minimum_required(VERSION 3.8.2)
cmake_policy(SET CMP0048 NEW)
project(clean-editor-lib VERSION 1.0.0 LANGUAGES C CXX)

###########################
# Dependencies
find_package(Qt5 COMPONENTS Core Gui REQUIRED)

###########################
# Targets
add_library(${PROJECT_NAME} SHARED
  #  Controllers
  src/main-router.cpp
  src/file-navigation-router.cpp
  src/editor-router.cpp
  src/menu-router.cpp

  src/file-handler.cpp
  src/document-handler.cpp
  src/documents-model.cpp
  src/editor-model.cpp
  src/abstract-editor-model.cpp
  src/menu-model.cpp

  #  Controllers
  public/main-router.h
  public/file-navigation-router.h
  public/editor-router.h
  public/menu-router.h

  public/globals.h
  public/file-handler.h
  public/document-handler.h
  public/documents-model.h
  public/editor-model.h
  public/abstract-editor-model.h
  public/menu-model.h
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
    Qt5::Gui
)

target_compile_features(${PROJECT_NAME}
  PUBLIC
    cxx_std_14
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    AUTOMOC ON
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

###########################
# Include tests

add_subdirectory(tests)
