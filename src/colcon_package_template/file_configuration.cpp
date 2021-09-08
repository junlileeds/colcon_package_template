/**
 * @file file_configuration.cpp
 * @author Jun Li
 * @copyright Copyright (c) 2021, University of Leeds and Harbin Institute of Technology.
 * @license License BSD-3-Clause
 * @date 2021-09-07
 */

#include "colcon_package_template/file_configuration.hpp"

namespace colcon_package_template
{

FileConfiguration::FileConfiguration(std::string yaml_file)
{
    try
    {
        YAML::Node node = YAML::LoadFile(yaml_file);
        this->kp_ = node["kp"].as<double>();
        this->kd_ = node["kd"].as<double>();
        this->ki_ = node["ki"].as<double>();

        this->error_ = false;
    }
    catch (const std::exception& e)
    {
        this->error_ = true;
        this->error_message_ = e.what();
    }
}

double FileConfiguration::get_kp() const
{
    return this->kp_;
}

double FileConfiguration::get_kd() const
{
    return this->kd_;
}

double FileConfiguration::get_ki() const
{
    return this->ki_;
}

bool FileConfiguration::has_error() const
{
    return this->error_;
}

std::string FileConfiguration::get_error() const
{
    return this->error_message_;
}

}  // namespace colcon_package_template