#include <string>

#include "behavior_trees/saludo.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

saludo::saludo(const std::string& name): BT::ActionNodeBase(name, {})
{

}

void saludo::halt()
{
  ROS_INFO("saludo halt");
}

BT::NodeStatus saludo::tick()
{
  ROS_INFO("saludo tick");
  //return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
