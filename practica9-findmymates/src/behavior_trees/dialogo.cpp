#include <string>

#include "behavior_trees/dialogo.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

dialogo::dialogo(const std::string& name, const BT::NodeConfiguration& config)
  : ActionNodeBase(name, config)
{

}

void dialogo::halt()
{
  ROS_INFO("dialogo halt");
}

BT::NodeStatus dialogo::tick()
{
  ROS_INFO("dialogo tick");
  setOutput("color", "rojo" );
  setOutput("personname", "minombre" );
  //return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList dialogo::providedPorts()
{
    return {
      BT::OutputPort<std::string>("color"),
      BT::OutputPort<std::string>("personname")
    };
}

}  // namespace behavior_trees
