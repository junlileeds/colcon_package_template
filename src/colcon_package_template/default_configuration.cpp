/**
 * @file default_configuration.cpp
 * @author Jun Li
 * @copyright Copyright (c) 2021, University of Leeds and Harbin Institute of Technology.
 * @license License BSD-3-Clause
 * @date 2021-09-07
 */

#include "colcon_package_template/default_configuration.hpp"

namespace colcon_package_template
{

double DefaultConfiguration::get_kp() const 
{
    return DEFAULT_KP;
}

double DefaultConfiguration::get_kd() const
{
    return DEFAULT_KD;
}

double DefaultConfiguration::get_ki() const
{
    return DEFAULT_KI;
}

bool DefaultConfiguration::has_error() const
{
    return false;
}

std::string DefaultConfiguration::get_error() const
{
    return std::string("no error");
}

}  // namespace colcon_package_template