cmake_minimum_required(VERSION 3.5)
project(saving)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav2_map_server REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(std_msgs REQUIRED)

# Include hpp files
include_directories(
  include
)

# Build saving executable
add_executable(saving
  src/main.cpp
  src/saving_node.cpp)
ament_target_dependencies(saving
  rclcpp
  nav2_map_server
  nav_msgs
  std_msgs)

# Install
install(TARGETS
  saving
  DESTINATION lib/${PROJECT_NAME})

ament_package()
