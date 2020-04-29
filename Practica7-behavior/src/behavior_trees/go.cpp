#include <string>

#include "behavior_trees/go.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

go::go(const std::string& name): BT::ActionNodeBase(name, {}), counter_(0)
{

}

void go::halt()
{
  ROS_INFO("go halt");
}

BT::NodeStatus go::tick()
{
  ROS_INFO("go tick %d", counter_);
  counter_++;
  if (counter_ < 5)
  {
    //move
    return BT::NodeStatus::RUNNING;
  }
  else
  {
    //stop moving
    counter_=0;
    return BT::NodeStatus::FAILURE;
  }
}

}  // namespace behavior_trees
