#include <string>

#include "behavior_trees/busca.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

busca::busca(const std::string& name): BT::ActionNodeBase(name, {})
{

}

void busca::halt()
{
  ROS_INFO("busca halt");
}

BT::NodeStatus busca::tick()
{
  ROS_INFO("busca tick");
  return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
