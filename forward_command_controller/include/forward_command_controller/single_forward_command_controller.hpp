// Copyright 2020 PAL Robotics S.L.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FORWARD_COMMAND_CONTROLLER__SINGLE_FORWARD_COMMAND_CONTROLLER_HPP_
#define FORWARD_COMMAND_CONTROLLER__SINGLE_FORWARD_COMMAND_CONTROLLER_HPP_

#include <memory>
#include <string>

#include "controller_interface/controller_interface.hpp"
#include "forward_command_controller/visibility_control.h"
#include "hardware_interface/joint_handle.hpp"
#include "rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp"
#include "rclcpp_lifecycle/state.hpp"
#include "rclcpp/subscription.hpp"
#include "realtime_tools/realtime_buffer.h"
#include "std_msgs/msg/float64.hpp"

namespace forward_command_controller
{

/**
 * \brief Forward command controller for a single joint.
 *
 * This class forwards the command signal down to a joint
 * on the specified interface.
 *
 * \param joint Name of the joint to control.
 * \param interface_name Name of the interface to command.
 *
 * Subscribes to:
 * - \b command (std_msgs::msg::Float64) : The command to apply.
 */
class SingleForwardCommandController : public controller_interface::ControllerInterface
{
public:
  FORWARD_COMMAND_CONTROLLER_PUBLIC
  SingleForwardCommandController();

  FORWARD_COMMAND_CONTROLLER_PUBLIC
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_configure(const rclcpp_lifecycle::State & previous_state) override;

  FORWARD_COMMAND_CONTROLLER_PUBLIC
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_activate(const rclcpp_lifecycle::State & previous_state) override;

  FORWARD_COMMAND_CONTROLLER_PUBLIC
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_deactivate(const rclcpp_lifecycle::State & previous_state) override;

  FORWARD_COMMAND_CONTROLLER_PUBLIC
  controller_interface::return_type
  update() override;

protected:
  using CmdType = std_msgs::msg::Float64;

  std::shared_ptr<hardware_interface::JointHandle> joint_cmd_handle_;
  realtime_tools::RealtimeBuffer<std::shared_ptr<CmdType>> rt_command_ptr_;
  rclcpp::Subscription<CmdType>::SharedPtr joint_command_subscriber_;

  std::string logger_name_;
};

}  // namespace forward_command_controller

#endif  // FORWARD_COMMAND_CONTROLLER__SINGLE_FORWARD_COMMAND_CONTROLLER_HPP_
