#include <string>

#include "behavior_trees/saluda.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

saluda::saluda(const std::string& name): BT::ActionNodeBase(name, {}), counter_(0)
{

}

void saluda::halt()
{
  ROS_INFO("saluda halt");
}

BT::NodeStatus saluda::tick()
{
  ROS_INFO("saluda tick %d", counter_);
  counter_++;
  if (counter_ < 5)
  {
    //move
    return BT::NodeStatus::RUNNING;
  }
  else
  {
    //stop moving
    return BT::NodeStatus::SUCCESS;
  }
}

}  // namespace behavior_trees
