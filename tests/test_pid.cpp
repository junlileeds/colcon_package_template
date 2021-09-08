/**
 * @file test_pid.hpp
 * @author Jun Li
 * @copyright Copyright (c) 2021, University of Leeds and Harbin Institute of Technology.
 * @license License BSD-3-Clause
 * @date 2021-09-07
 */

#include "colcon_package_template/file_configuration.hpp"
#include "colcon_package_template/pid.hpp"

#include <fstream>
#include <gtest/gtest.h>

#define YAML_CONFIG_FILE "package_template_unit_test.yaml"

/* *********** setup of test ********** */
class PidTest : public ::testing::Test
{
protected:
    void SetUp()
    {
        YAML::Node node;
        node["kp"] = DEFAULT_KP;
        node["kd"] = DEFAULT_KD;
        node["ki"] = DEFAULT_KI;
        std::ofstream fout(YAML_CONFIG_FILE);
        fout << node;
    }

    void TearDown()
    {
        std::remove(YAML_CONFIG_FILE);
    }
};

/* **************** testing DefaultConfiguration **************** */
TEST_F(PidTest, default_configuration_test)
{
    colcon_package_template::DefaultConfiguration config;
    ASSERT_EQ(config.get_kp(), DEFAULT_KP);
    ASSERT_EQ(config.get_kd(), DEFAULT_KD);
    ASSERT_EQ(config.get_ki(), DEFAULT_KI);
    ASSERT_EQ(config.has_error(), false);
}

/* ***************** testing FileConfiguration ***************** */
TEST_F(PidTest, file_configuration_ok_test)
{
    colcon_package_template::FileConfiguration config(YAML_CONFIG_FILE);
    ASSERT_EQ(config.get_kp(), DEFAULT_KP);
    ASSERT_EQ(config.get_kd(), DEFAULT_KD);
    ASSERT_EQ(config.get_ki(), DEFAULT_KI);
}

TEST_F(PidTest, file_configuration_fail_test)
{
    colcon_package_template::FileConfiguration config("None existing file");
    ASSERT_EQ(config.has_error(), true);
}

/* ************** with default configuration file ************** */
TEST_F(PidTest, read_config_file_test)
{
    colcon_package_template::FileConfiguration config(YAML_CONFIG_FILE);
    ASSERT_EQ(config.has_error(), false);
}

TEST_F(PidTest, configurations_same_results_test)
{
    // random data for testing
    double position = 1;
    double velocity = 1;
    double position_target = 2;
    double delta_time = 0.01;

    colcon_package_template::DefaultConfiguration default_config;
    colcon_package_template::PID controller_default(default_config);
    double force_default = controller_default.compute(
        position, velocity, position_target, delta_time);
    
    colcon_package_template::FileConfiguration file_config(YAML_CONFIG_FILE);
    colcon_package_template::PID controller_file(file_config);
    double force_file = controller_file.compute(
        position, velocity, position_target, delta_time);

    ASSERT_EQ(force_default, force_file);
}

// does integral integrates ?
TEST_F(PidTest, integral)
{
    // random data for testing
    double position = 1;
    double velocity = 1;
    double position_target = 2;
    double delta_time = 0.01;

    colcon_package_template::PID& controller = colcon_package_template::getDefaultPid();
    double force_1 = controller.compute(position, velocity, position_target, delta_time);
    double force_2 = controller.compute(position, velocity, position_target, delta_time);

    ASSERT_NE(force_1, force_2);
}

// does reset of integral work?
TEST_F(PidTest, reset_integral)
{
    // random data for testing
    double position = 1;
    double velocity = 1;
    double position_target = 2;
    double delta_time = 0.01;

    // running pid and integrating
    colcon_package_template::PID& controller = colcon_package_template::getDefaultPid();
    double force_1 = controller.compute(position, velocity, position_target, delta_time);

    // reset integral
    controller.reset_integral();

    // run controller again
    double force_reset = controller.compute(position, velocity, position_target, delta_time);

    ASSERT_EQ(force_1, force_reset);
}

// generated force is zero if already at target?
TEST_F(PidTest, zero_force_at_target)
{
    // random data for testing
    double position = 1;
    double velocity = 0;
    double position_target = position;
    double delta_time = 0.01;

    colcon_package_template::PID& controller = colcon_package_template::getDefaultPid();
    double force = controller.compute(position, velocity, position_target, delta_time);

    ASSERT_EQ(force, 0);
}

// does the controller push to the right direction ?
TEST_F(PidTest, right_direction)
{
    // random data for testing
    double position = 0;
    double velocity = 0;
    double position_target = 1;
    double delta_time = 0.01;

    colcon_package_template::PID& controller = colcon_package_template::getDefaultPid();
    double force = controller.compute(position, velocity, position_target, delta_time);
    ASSERT_GT(force, 0);

    controller.reset_integral();
    position_target = -1;
    force = controller.compute(position, velocity, position_target, delta_time);
    ASSERT_LT(force, 0);

    controller.reset_integral();
    position_target = position;
    velocity = -1;
    force = controller.compute(position, velocity, position_target, delta_time);
    ASSERT_GT(force, 0);

    controller.reset_integral();
    velocity = 1;
    force = controller.compute(position, velocity, position_target, delta_time);
    ASSERT_LT(force, 0);
}