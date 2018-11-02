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
  public/main-controller.h
  public/globals.h
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
    cxx_std_11
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    AUTOMOC ON
)

###########################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/CleanEditor)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_NAME CleanEditor)

install(DIRECTORY public/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT ${PROJECT_NAME}-targets
  FILE
    CleanEditorTargets.cmake
  NAMESPACE
    CleanEditor::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/CleanEditorConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/CleanEditorConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/CleanEditorConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/CleanEditorConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/CleanEditorConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree

export(EXPORT ${PROJECT_NAME}-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/CleanEditorTargets.cmake NAMESPACE CleanEditor::)

#Register package in user's package registry
export(PACKAGE CleanEditor)

##############################################
## Include tests

add_subdirectory(tests)
