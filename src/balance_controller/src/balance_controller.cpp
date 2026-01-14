#include "balance_controller/balance_controller.hpp"
#include "pluginlib/class_list_macros.hpp"

namespace balance_controller
{

    controller_interface::CallbackReturn BalanceController::on_init()
    {
        return controller_interface::CallbackReturn::SUCCESS;
    }

    controller_interface::InterfaceConfiguration BalanceController::command_interface_configuration() const
    {
        controller_interface::InterfaceConfiguration config;
        config.type = controller_interface::interface_configuration_type::INDIVIDUAL;
        // Claim velocity interfaces for wheels
        config.names.push_back("Wheel_L_Joint/effort");
        config.names.push_back("Wheel_R_Joint/effort");
        return config;
    }

    controller_interface::InterfaceConfiguration BalanceController::state_interface_configuration() const
    {
        controller_interface::InterfaceConfiguration config;
        config.type = controller_interface::interface_configuration_type::INDIVIDUAL;

        config.names.push_back("Wheel_L_Joint/velocity");
        config.names.push_back("Wheel_R_Joint/velocity");

        config.names.push_back("Wheel_L_Joint/position");
        config.names.push_back("Wheel_R_Joint/position");
        return config;
    }

    controller_interface::return_type BalanceController::update(const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
    {
        // 1. Get states from state_interfaces_
        // 2. Calculate LQR: $u = -K \mathbf{x}$
        // 3. Write to command_interfaces_
        return controller_interface::return_type::OK;
    }

} // namespace balance_controller

PLUGINLIB_EXPORT_CLASS(balance_controller::BalanceController, controller_interface::ControllerInterface)