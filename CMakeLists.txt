#
# Copyright (c) 2021, Jun Li, University of Leeds and Harbin Institute of Technology.
#
# License BSD-3 clause
#

cmake_minimum_required(VERSION 3.10.2)

project(colcon_package_template VERSION 2.0.0)

# Using C++17
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")


#
# Dependencies
#

# local
find_package(yaml_utils REQUIRED)
find_package(mpi_cmake_modules REQUIRED)
find_package(pybind11 REQUIRED)


# prepare to export all needed targets
set(all_targets)
set(all_exec_targets)


#
# Library
#
add_library(
  ${PROJECT_NAME} SHARED
    src/${PROJECT_NAME}/gains_configuration.cpp
    src/${PROJECT_NAME}/default_configuration.cpp
    src/${PROJECT_NAME}/file_configuration.cpp
    src/${PROJECT_NAME}/pid.cpp)
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include>)
target_link_libraries(${PROJECT_NAME} yaml_utils::yaml_utils)
list(APPEND all_targets ${PROJECT_NAME})


#
# Python wrappers
#
pybind11_add_module(py${PROJECT_NAME} MODULE srcpy/${PROJECT_NAME}/wrappers.cpp)
target_include_directories(py${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_link_libraries(py${PROJECT_NAME} PRIVATE pybind11::module)
target_link_libraries(py${PROJECT_NAME} PRIVATE ${PROJECT_NAME})
list(APPEND all_targets py${PROJECT_NAME})


#
# Demos
#
# demo_pid
add_executable(${PROJECT_NAME}_demo_pid demos/demo_pid.cpp)
target_include_directories(
  ${PROJECT_NAME}_demo_pid
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)
target_link_libraries(${PROJECT_NAME}_demo_pid ${PROJECT_NAME})
list(APPEND all_exec_targets ${PROJECT_NAME}_demo_pid)
# demo_pid_load_from_file
add_executable(${PROJECT_NAME}_demo_pid_load_from_file demos/demo_pid_load_from_file.cpp)
target_include_directories(
  ${PROJECT_NAME}_demo_pid_load_from_file
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)
target_link_libraries(${PROJECT_NAME}_demo_pid_load_from_file ${PROJECT_NAME})
target_compile_definitions(
  ${PROJECT_NAME}_demo_pid_load_from_file
  PUBLIC
    TEST_PID_GAINS_YAML_FILE_PATH="${PROJECT_SOURCE_DIR}/config/test_pid_gains.yaml"
  )
list(APPEND all_exec_targets ${PROJECT_NAME}_demo_pid_load_from_file)

# append to all target
list(APPEND all_targets ${all_exec_targets})


#
# Unit tests
#
include(CTest)
if(BUILD_TESTING)
  # C++ unit-tests framework used.
  find_package(GTest CONFIG REQUIRED)
  include(GoogleTest)
  # Config folder
  get_filename_component(CONFIG_PATH config ABSOLUTE)
  # create the executable
  add_executable(test_${PROJECT_NAME} tests/gtest_main.cpp
                                      tests/test_pid.cpp)
  # link to the created librairies and its dependencies
  target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME})
  target_link_libraries(test_${PROJECT_NAME} GTest::gtest)
  # create 2 macro: the path to the config file and the path to the data file
  target_compile_definitions(
    test_${PROJECT_NAME}
    PUBLIC CONFIG_PATH="${CONFIG_PATH}"
           TEST_PID_GAINS_YAML_FILE_PATH="${CONFIG_PATH}/test_pid_gains.yaml")
  # declare the test as gtest
  gtest_add_tests(TARGET test_${PROJECT_NAME})

  find_program(py_executable "python3")
  if(py_executable)
    add_test(
      NAME test_${PROJECT_NAME}_python
      COMMAND ${py_executable} -m pytest -v
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)
    set_tests_properties(
      test_${PROJECT_NAME}_python
      PROPERTIES
        ENVIRONMENT
        "PYTHONPATH=${PROJECT_SOURCE_DIR}/python:${CMAKE_BINARY_DIR}:$ENV{PYTHONPATH}"
    )
  endif()
endif()


#
# Install and export.
#

# install the include directory
install(DIRECTORY include/ DESTINATION include)
# install the config folder
install(DIRECTORY config DESTINATION share/${PROJECT_NAME})
# install the library
install(
  TARGETS  ${all_targets}
  EXPORT   ${PROJECT_NAME}Targets
  LIBRARY  DESTINATION lib
  ARCHIVE  DESTINATION lib
  RUNTIME  DESTINATION lib/${PROJECT_NAME}
  INCLUDES DESTINATION include
)

# Install symlink in bin for the executables as well
foreach(target ${all_exec_targets})
  # install a symlink of the executable in lib/teststand
  string(
    CONCAT symlink_command
           "execute_process("
           "  COMMAND ${CMAKE_COMMAND} -E make_directory "
           "  ${CMAKE_INSTALL_PREFIX}/bin/)\n"
           "execute_process("
           "  COMMAND ${CMAKE_COMMAND} -E create_symlink "
           "  ${CMAKE_INSTALL_PREFIX}/lib/${PROJECT_NAME}/${target}"
           "  ${CMAKE_INSTALL_PREFIX}/bin/${target} )")
  install(CODE ${symlink_command})
endforeach(target ${all_exec_targets})

get_python_install_dir(python_install_dir)
# install the wrappers 
install(TARGETS py${PROJECT_NAME} DESTINATION ${python_install_dir})
# install the python package too
install(
  DIRECTORY python/${PROJECT_NAME}
  DESTINATION ${python_install_dir}
  PATTERN "*.pyc" EXCLUDE
  PATTERN "__pycache__" EXCLUDE
)


#
# Export this package as a cmake package.
#
generate_cmake_package()
