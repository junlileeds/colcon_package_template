/**
 * @file pid.cpp
 * @author Jun Li
 * @copyright Copyright (c) 2021, University of Leeds and Harbin Institute of Technology.
 * @license License BSD-3-Clause
 * @date 2021-09-07
 */

#include "colcon_package_template/pid.hpp"

namespace colcon_package_template
{

PID::PID() : integral_(0)
{
    configuration_ = new DefaultConfiguration();
    private_configuration_ = true;
}

PID::PID(const GainsConfiguration& configuration)
    : configuration_(&configuration), 
      private_configuration_(false), 
      integral_(0) 
{
}

PID::~PID()
{
    if (private_configuration_)
    {
        delete configuration_;
    }
}

void PID::reset_integral()
{
    this->integral_ = 0;
}

double PID::compute(const double position, const double velocity, 
                    const double position_target, const double delta_time)
{
    double position_error = position_target - position;
    this->integral_ += delta_time * position_error;
    double f = position_error * configuration_->get_kp() - 
               velocity * configuration_->get_kd() + 
               this->integral_ * configuration_->get_ki();
    return f;
}

/**
 * @brief Use a PID factory for the unittests.
 */
class DefaultPidFactory
{
public:
    /*! The PID gains. */
    static std::vector<std::shared_ptr<GainsConfiguration>> configs_;
    /*! List of PID controllers. */
    static std::vector<std::shared_ptr<PID>> controllers_;

    /**
     * @brief PID controller factory.
     * @return PID& Return a reference to a newly created PID controller.
     */
    static PID& get()
    {
        std::shared_ptr<GainsConfiguration> configuration(new DefaultConfiguration());
        std::shared_ptr<PID> controller(new PID(*configuration));
        configs_.push_back(configuration);
        controllers_.push_back(controller);
        return *controller;
    }
};

std::vector<std::shared_ptr<GainsConfiguration>> DefaultPidFactory::configs_;
std::vector<std::shared_ptr<PID>> DefaultPidFactory::controllers_;

PID& getDefaultPid()
{
    return DefaultPidFactory::get();
}

}  // namespace colcon_package_template