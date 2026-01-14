#pragma once

#include "controller_interface/controller_interface.hpp"
#include "rclcpp/rclcpp.hpp"

namespace balance_controller
{

    class BalanceController : public controller_interface::ControllerInterface
    {
    public:
        controller_interface::CallbackReturn on_init() override;
        controller_interface::InterfaceConfiguration command_interface_configuration() const override;
        controller_interface::InterfaceConfiguration state_interface_configuration() const override;
        controller_interface::return_type update(const rclcpp::Time &time, const rclcpp::Duration &period) override;
        rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
        double theta_{0.0};
        double theta_dot_{0.0};

    private:
        // LQR state: [x, x_dot, theta, theta_dot]
        // Gains: u = -K * x
        double K_[4] = {0.0, 0.5, 15.0, 2.0};
    };

} // namespace balance_controller