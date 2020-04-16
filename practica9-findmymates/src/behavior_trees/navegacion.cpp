#include <string>

#include "behavior_trees/navegacion.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

navegacion::navegacion(const std::string& name): BT::ActionNodeBase(name, {})
{

}

void navegacion::halt()
{
  ROS_INFO("navegacion halt");
}

BT::NodeStatus navegacion::tick()
{
  ROS_INFO("navegacion tick");
  //return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
