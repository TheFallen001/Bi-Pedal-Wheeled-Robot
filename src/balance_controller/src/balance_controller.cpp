#include "balance_controller/balance_controller.hpp"
#include "pluginlib/class_list_macros.hpp"

controller_interface::CallbackReturn BalanceController::on_init()
{
  auto node = get_node();

  imu_sub_ = node->create_subscription<sensor_msgs::msg::Imu>(
    "/imu", 10,
    [this](sensor_msgs::msg::Imu::SharedPtr msg)
    {
      // Pitch angle approximation (small angles)
      theta_ = msg->orientation.y;
      theta_dot_ = msg->angular_velocity.y;
    });

  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn BalanceController::on_activate(
  const rclcpp_lifecycle::State &)
{
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn BalanceController::on_deactivate(
  const rclcpp_lifecycle::State &)
{
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::return_type BalanceController::update(
  const rclcpp::Time &,
  const rclcpp::Duration &)
{
  // Get wheel velocities
  double x_dot = state_interfaces_[0].get_value(); // left wheel
  double x = 0.0; // optional (ignore initially)

  // LQR control
  double u =
    -K_[0]*x
    -K_[1]*x_dot
    -K_[2]*theta_
    -K_[3]*theta_dot_;

  // Send torque to wheels
  command_interfaces_[0].set_value(u);
  command_interfaces_[1].set_value(u);

  return controller_interface::return_type::OK;
}

PLUGINLIB_EXPORT_CLASS(
  BalanceController,
  controller_interface::ControllerInterface)
