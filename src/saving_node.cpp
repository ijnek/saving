// Copyright 2021 Kenji Brameld
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

#include <memory>
#include "saving/saving_node.hpp"
#include "nav2_map_server/map_io.hpp"

using std::placeholders::_1;

SavingNode::SavingNode()
: Node("SavingNode")
{
  // Subscription for map
  mapSubscription = this->create_subscription<nav_msgs::msg::OccupancyGrid>(
      "map", 10, std::bind(&SavingNode::callbackMap, this, _1));

  // Subscription for "stop" msg
  cmdSubscription = this->create_subscription<std_msgs::msg::String>(
      "cmd", 10, std::bind(&SavingNode::callbackCmd, this, _1));
}

void SavingNode::callbackMap(const nav_msgs::msg::OccupancyGrid::SharedPtr msg)
{
  // Store map to class variable
  map = *msg;
}

void SavingNode::callbackCmd(const std_msgs::msg::String::SharedPtr msg)
{
  if (msg->data == "stop") {
    nav2_map_server::SaveParameters params;
    params.map_file_name = "bla";
    params.free_thresh = 0.25;
    params.occupied_thresh = 0.65;

    nav_msgs::msg::OccupancyGrid map;
    nav2_map_server::saveMapToFile(map, params);
  }
}
