#include <string>

#include "behavior_trees/informacion.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"
#include "sound_play/sound_play.h"

namespace behavior_trees
{

informacion::informacion(const std::string& name): BT::ActionNodeBase(name, {})
{

}

void informacion::halt()
{
  ROS_INFO("informacion halt");
}

BT::NodeStatus informacion::tick()
{
  ROS_INFO("informacion tick");
  //return BT::NodeStatus::RUNNING;
  sound_play::SoundClient sc;
  sc.say("");

  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
