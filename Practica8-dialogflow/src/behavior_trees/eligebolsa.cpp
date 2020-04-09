#include <string>

#include "behavior_trees/eligebolsa.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

eligebolsa::eligebolsa(const std::string& name): BT::ActionNodeBase(name, {}), counter_(0)
{

}

void eligebolsa::halt()
{
  ROS_INFO("eligebolsa halt");
}

BT::NodeStatus eligebolsa::tick()
{
  ROS_INFO("eligebolsa tick %d", counter_);
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
