cmake_minimum_required(VERSION 3.8)
project(balance_controller)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(controller_interface REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(sensor_msgs REQUIRED)


add_library(${PROJECT_NAME} SHARED
  src/balance_controller.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
  include
)
ament_target_dependencies(${PROJECT_NAME}
  controller_interface
  hardware_interface
  pluginlib
  rclcpp
  sensor_msgs
)

pluginlib_export_plugin_description_file(
  controller_interface plugin.xml
)

# 3. Prevent "Undefined Reference" errors during loading
# This ensures the library is correctly linked
target_compile_definitions(${PROJECT_NAME} PRIVATE "BALANCE_CONTROLLER_BUILDING_DLL")

# 4. Install instructions
install(TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(FILES plugin.xml 
  DESTINATION share/${PROJECT_NAME}
)

# 5. Export for ROS 2 discovery
ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  controller_interface
  hardware_interface
  pluginlib
  rclcpp
  sensor_msgs
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
