#include <string>

#include "behavior_trees/vuelve.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

vuelve::vuelve(const std::string& name): BT::ActionNodeBase(name, {})
{

}

void vuelve::halt()
{
  ROS_INFO("vuelve halt");
}

BT::NodeStatus vuelve::tick()
{
  ROS_INFO("vuelve tick");
  //return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
