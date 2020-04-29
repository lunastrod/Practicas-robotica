#include <string>

#include "behavior_trees/turn.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

turn::turn(const std::string& name): BT::ActionNodeBase(name, {}), counter_(0)
{

}

void turn::halt()
{
  ROS_INFO("turn halt");
}

BT::NodeStatus turn::tick()
{
  ROS_INFO("turn tick %d", counter_);
  counter_++;
  if (counter_ < 5)
  {
    //turn
    return BT::NodeStatus::RUNNING;
  }
  else
  {
    //stop turning
    counter_=0;
    return BT::NodeStatus::FAILURE;
  }
}

}  // namespace behavior_trees
