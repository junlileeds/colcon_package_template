/**
 * @file gains_configuration.cpp
 * @author Jun Li
 * @copyright Copyright (c) 2021, University of Leeds and Harbin Institute of Technology.
 * @license License BSD-3-Clause
 * @date 2021-09-07
 */

#include "colcon_package_template/gains_configuration.hpp"

namespace colcon_package_template
{

void printConfiguration(const GainsConfiguration& configuration)
{
    std::cout << "kp: " << configuration.get_kp() << std::endl;
    std::cout << "kd: " << configuration.get_kd() << std::endl;
    std::cout << "ki: " << configuration.get_ki() << std::endl;
}

}  // namespace colcon_package_template