#include <string>

#include "behavior_trees/dialogo.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

dialogo::dialogo(const std::string& name): BT::ActionNodeBase(name, {})
{

}

void dialogo::halt()
{
  ROS_INFO("dialogo halt");
}

BT::NodeStatus dialogo::tick()
{
  ROS_INFO("dialogo tick");
  //return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
