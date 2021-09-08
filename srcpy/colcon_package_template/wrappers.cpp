/**
 * @file wrappers.cpp
 * @author Jun Li
 * @copyright Copyright (c) 2021, University of Leeds and Harbin Institute of Technology.
 * @license License BSD-3-Clause
 * @date 2021-09-08
 */

#include "colcon_package_template/pid.hpp"

#include <pybind11/pybind11.h>

using namespace colcon_package_template;

PYBIND11_MODULE(pycolcon_package_template, m)
{
    pybind11::class_<PID>(m, "PID")
        .def(pybind11::init<>())
        .def("reset_integral", &PID::reset_integral)
        .def("compute", &PID::compute);
}