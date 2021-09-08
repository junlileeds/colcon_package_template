/**
 * @file pid.hpp
 * @author Jun Li
 * @copyright Copyright (c) 2021, University of Leeds and Harbin Institute of Technology.
 * @license License BSD-3-Clause
 * @date 2021-09-07
 */

#pragma once

#include <vector>
#include <memory>
#include "colcon_package_template/default_configuration.hpp"

namespace colcon_package_template
{

/**
 * @brief Simple 1D pid controller.
 */
class PID
{
public:
    /*! @brief Construct a default PID object using the DefaultConfiguration */
    PID();
    /*! @brief Construct a new PID object using user provided configuration. */
    PID(const GainsConfiguration& configuration);
    ~PID();

    /**
     * @brief Compute the force related to the pid controller.
     * Call resetIntegral() to reset the integral part.
     * @param[in] position current position.
     * @param[in] velocity current_velocity.
     * @param[in] position_target target position.
     * @param[in] delta_time time passed since last measurement. Used for integral
     *            computation.
     * @return computed force.
     */
    double compute(const double position, const double velocity, 
                   const double position_target, const double delta_time);

    /*! @brief Reset integral part of the PID */
    void reset_integral();

private:
    const GainsConfiguration* configuration_;
    bool private_configuration_;
    double integral_;
};

/**
 * Convenience factory for getting default controller, 
 * i.e. same as PID(std::shared_ptr<DefaultConfiguration> configuration)
 */
PID& getDefaultPid();

}  // namespace colcon_package_template