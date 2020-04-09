#include <string>

#include "behavior_trees/cogebolsa.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

cogebolsa::cogebolsa(const std::string& name): BT::ActionNodeBase(name, {}), counter_(0)
{

}

void cogebolsa::halt()
{
  ROS_INFO("cogebolsa halt");
}

BT::NodeStatus cogebolsa::tick()
{
  ROS_INFO("cogebolsa tick %d", counter_);
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
