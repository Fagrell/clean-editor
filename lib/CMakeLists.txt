cmake_minimum_required(VERSION 3.8.2)
cmake_policy(SET CMP0048 NEW)
project(clean-editor-lib VERSION 1.0.0 LANGUAGES C CXX)

###########################
# Dependencies
find_package(Qt6 COMPONENTS Core Gui REQUIRED)

###########################
# Targets
add_library(${PROJECT_NAME} SHARED
  # Src
  ## Controllers
  src/controllers/main-controller.cpp
  src/controllers/file-navigation-controller.cpp
  src/controllers/editor-controller.cpp
  src/controllers/menu-controller.cpp

  ## Models
  src/models/documents-model.cpp
  src/models/editor-model.cpp
  src/models/abstract-editor-model.cpp
  src/models/menu-model.cpp
  src/models/file-navigation-model.cpp

  src/file-handler.cpp
  src/document-handler.cpp

  # Public
  ## Controllers
  public/controllers/main-controller.h
  public/controllers/file-navigation-controller.h
  public/controllers/editor-controller.h
  public/controllers/menu-controller.h

  ## Models
  public/models/documents-model.h
  public/models/editor-model.h
  public/models/abstract-editor-model.h
  public/models/menu-model.h
  public/models/file-navigation-model.h

  public/globals.h
  public/file-handler.h
  public/document-handler.h
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:
      public
      public/controllers
      public/models
     >
    $<BUILD_INTERFACE:
      ${CMAKE_CURRENT_SOURCE_DIR}/public
      ${CMAKE_CURRENT_SOURCE_DIR}/public/controllers
      ${CMAKE_CURRENT_SOURCE_DIR}/public/models
     >
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/controllers
    ${CMAKE_CURRENT_SOURCE_DIR}/src/models
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE
    CLEAN_EDITOR_LIBRARY
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    Qt6::Core
    Qt6::Gui
)

target_compile_features(${PROJECT_NAME}
  PUBLIC
    cxx_std_17
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
