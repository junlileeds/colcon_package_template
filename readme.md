colcon_package_template
-----------------------

This repository is a tutorial on how to package C++ and Python code together.

In particular it contains the examples for:
- Packaging C++ and Python code in one repository.
- How to build C++ code and package it with CMake.
- How to write a PID controller in C++.
- How to write a PID controller in Python.
- How to write Python bindings over the C++ code using [Pybind11](https://github.com/pybind/pybind11)
- How to write unit-tests in C++ and Python.
- How to deal with YAML configuration files from C++ or Python.
- How to write C++ and Python demos of the code.
- How to write the API documentation using:
    - Doxygen docstring for C++, 
    - Google docstring for Python, 
    - Markdown or Restructured text for generic documentation.


### Installation:

#### Standard dependencies:

This package depend externally on:
- cmake_modules for the build system
- pybind11 for the python bindings
- yaml_utils for the yaml parsing in C++
- googletest for the C++ unit tests
- pytest for the Python unit tests

In short for the external dependencies without the doc ones:
Install YAML:
```
sudo apt install libyaml-cpp-dev
```
Install Google Test
```
sudo apt install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
```
Install pytest
```
python3 -m pip install -U pytest
```

#### Download the package:

```
git clone git@github.com:junlileeds/colcon_package_template.git
```

#### Build the package

We use colcon to build the package:
```
cd mkdir -p ~/devel/workspace
colcon build
```


### Usage:

#### Demos/Examples

The purpose of this code is for user to read it.
But you can still start the demos compiled with this package:
```
colcon_package_template_demo_pid
```
or
```
colcon_package_template_demo_pid_load_from_file
```

#### API documentation

Building the documentation locally:
```
colcon build --packages-select colcon_package_template --cmake-args -DGENERATE_DOCUMENTATION=ON
```


### License and Copyrights

License BSD-3-Clause
Copyright (c) 2021, Jun Li, University of Leeds and Harbin Institute of Technology.
