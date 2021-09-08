/**
 * @file file_configuration.hpp
 * @author Jun Li
 * @copyright Copyright (c) 2021, University of Leeds and Harbin Institute of Technology.
 * @license License BSD-3-Clause
 * @date 2021-09-07
 */

#pragma once

#include <yaml_utils/yaml_cpp_fwd.hpp>
#include "colcon_package_template/gains_configuration.hpp"

namespace colcon_package_template
{

/**
 * @brief Reading configuration from yaml file.
 */
class FileConfiguration : public GainsConfiguration
{
public:
    /**
     * @brief Returns error encountered when reading configuration.
     * @param[in]  yaml_file absolute path to configuration yaml file. The file
     *             is expected to have parameters "kp", "kd" and "ki".
     */
    FileConfiguration(std::string yaml_file);

    double get_kp() const;
    double get_kd() const;
    double get_ki() const;

    bool has_error() const;
    std::string get_error() const;

private:
    // Proportional gain.
    double kp_;
    // Derivative gain.
    double kd_;
    // Integral gain.
    double ki_;
    // Internal error message.
    std::string error_message_;
    // True if an error occured.
    bool error_;
};

}  // namespace colcon_package_template