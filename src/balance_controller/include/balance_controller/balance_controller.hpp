#pragma once

#include "controller_interface/controller_interface.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"

class BalanceController : public controller_interface::ControllerInterface
{
public:
    controller_interface::CallbackReturn on_init() override;
    controller_interface::CallbackReturn on_activate(
        const rclcpp_lifecycle::State &previous_state) override;
    controller_interface::CallbackReturn on_deactivate(
        const rclcpp_lifecycle::State &previous_state) override;

    controller_interface::return_type update(
        const rclcpp::Time &time,
        const rclcpp::Duration &period) override;

private:
    // IMU state
    double theta_{0.0};
    double theta_dot_{0.0};

    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;

    // LQR gains (temporary hardcoded)
    double K_[4] = {0.0, 0.5, 15.0, 2.0}; // x, xdot, theta, thetadot
};
