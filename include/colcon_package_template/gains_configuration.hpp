/**
 * @file gains_configuration.hpp
 * @author Jun Li
 * @copyright Copyright (c) 2021, University of Leeds and Harbin Institute of Technology.
 * @license License BSD-3-Clause
 * @date 2021-09-07
 */

#pragma once

#include <iostream>
#include <string>

namespace colcon_package_template
{

/**
 * @brief Abstract class defining for the PID configuration.
 * 
 * This virtual object describes the configuration a PID objects id waiting
 * for. Daughter class will for example be initialize through files.
 */
class GainsConfiguration
{
public:
    /**
     * @brief The default destructor do nothing.
     */
    virtual ~GainsConfiguration() {}

    /**
     * @brief Get the proportional gain.
     * @return double
     */
    virtual double get_kp() const = 0;

    /**
     * @brief Get the derivative gain.
     * @return double
     */
    virtual double get_kd() const = 0;

    /**
     * @brief Get the integral gain.
     * @return double
     */
    virtual double get_ki() const = 0;

    /**
     * @brief Enquire if an error was encountered while reading the configuration.
     * @return true if an error has been encountered, false otherwise.
     */
    virtual bool has_error() const = 0;

    /**
     * @brief Return error encountered when reading configuration.
     */
    virtual std::string get_error() const = 0;
};

/**
 * Print values encapsulated by the provided configuration console on the 
 * standard output.
 */
void printConfiguration(const GainsConfiguration& configuration);

}  // namespace colcon_package_template