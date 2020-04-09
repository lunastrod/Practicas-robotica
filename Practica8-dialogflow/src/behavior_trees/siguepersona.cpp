#include <string>

#include "behavior_trees/siguepersona.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

siguepersona::siguepersona(const std::string& name): BT::ActionNodeBase(name, {}), counter_(0)
{

}

void siguepersona::halt()
{
  ROS_INFO("siguepersona halt");
}

BT::NodeStatus siguepersona::tick()
{
  ROS_INFO("siguepersona tick %d", counter_);
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
