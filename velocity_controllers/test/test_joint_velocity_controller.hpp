// Copyright 2020 PAL Robotics SL.
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

#ifndef TEST_JOINT_VELOCITY_CONTROLLER_HPP_
#define TEST_JOINT_VELOCITY_CONTROLLER_HPP_

#include <memory>
#include <string>

#include "gtest/gtest.h"

#include "hardware_interface/joint_handle.hpp"
#include "velocity_controllers/joint_velocity_controller.hpp"
#include "test_robot_hardware/test_robot_hardware.hpp"

// subclassing and friending so we can access member varibles
class FriendJointVelocityController : public velocity_controllers::JointVelocityController
{
  FRIEND_TEST(JointVelocityControllerTest, ConfigureParamsTest);
  FRIEND_TEST(JointVelocityControllerTest, CheckParamsTest);
};

class JointVelocityControllerTest : public ::testing::Test
{
public:
  static void SetUpTestCase();
  static void TearDownTestCase();

  void SetUp();
  void TearDown();

  void SetUpController();
  void SetUpHandles();

protected:
  std::shared_ptr<test_robot_hardware::TestRobotHardware> test_robot_;
  std::unique_ptr<FriendJointVelocityController> controller_;

  std::shared_ptr<hardware_interface::JointHandle> joint1_vel_cmd_handle_;
  std::shared_ptr<hardware_interface::JointHandle> joint2_vel_cmd_handle_;
  std::shared_ptr<hardware_interface::JointHandle> joint3_vel_cmd_handle_;
};

#endif  // TEST_JOINT_VELOCITY_CONTROLLER_HPP_
