/**
 * @file demo_pid.hpp
 * @author Jun Li
 * @copyright Copyright (c) 2021, University of Leeds and Harbin Institute of Technology.
 * @license License BSD-3-Clause
 * @date 2021-09-07
 * 
 * Create the default PID controller and compute the control once. This illustrates
 * in the simplest way the use of the PID class API.
 */

#include "colcon_package_template/pid.hpp"

/**
 * @brief Creates a PID controller and use the API in a small demo.
 */
void run_demo()
{
    // PID controller with default gains values
    colcon_package_template::PID& controller = colcon_package_template::getDefaultPid();

    // example of force computation
    double current_position = 1;
    double current_velocity = 1;
    double delta_time = 0.01;
    double target_position = 2;
    double force = controller.compute(
        current_position, current_velocity, target_position, delta_time);
    std::cout << "computed force: " << force << std::endl;

    // resetting integral of the controller
    // (useless here because we do not reuse it)
    controller.reset_integral();
}

/**
 * @brief Execute the run_demo() through a try/catch expression.
 * @return int
 */
int main()
{
    try
    {
        run_demo();
    }
    catch (const std::exception& e)
    {
        std::cout << "demo failed !\nerror message:\n" << e.what() << std::endl;
        return 1;  // this demo did not run successfully.
    }

    return 0;  // this demo did run successfully.
}
