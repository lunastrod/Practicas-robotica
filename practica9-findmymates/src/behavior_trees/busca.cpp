#include <string>

#include "behavior_trees/busca.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

busca::busca(const std::string& name, const BT::NodeConfiguration& config)
  : ActionNodeBase(name, config)
{

}

void busca::halt()
{
  ROS_INFO("busca halt");
}

BT::NodeStatus busca::tick()
{


  setOutput("pos", "cocina" );
  ROS_INFO("busca tick");
  //return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList busca::providedPorts()
{
    // This action has a single input port called "message"
    // Any port must have a name. The type is optional.
    return { BT::OutputPort<std::string>("pos") };
}

}  // namespace behavior_trees
