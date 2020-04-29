#include <string>

#include "behavior_trees/navegacion.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

#include "constants.h"

namespace behavior_trees
{

navegacion::navegacion(const std::string& name, const BT::NodeConfiguration& config)
  : ActionNodeBase(name, config)
{
  pub_goal=n.advertise<geometry_msgs::Point>("/navigator/goals",1);
  pub_vel_ =  n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  sub_running = n.subscribe("/navigator/isrunning",1,&navegacion::running_callback, this);
}

void navegacion::running_callback(const std_msgs::Bool& running){
  if(active && !running.data){
    ROS_INFO("he llegado al objetivo\n");
    navegando=false;
  }
}

void navegacion::halt()
{
  ROS_INFO("navegacion halt");
}

BT::NodeStatus navegacion::tick()
{
  active=true;
  if(!navegando){
    active=false;
    return BT::NodeStatus::SUCCESS;
  }
  BT::Optional<std::string> pos = getInput<std::string>("getpos");
  if (!pos)
  {
    throw BT::RuntimeError("missing required input [message]: ",
                         pos.error() );
  }
  std::string lugar=pos.value();
  std::cout << "current goal: " << lugar << std::endl;

  if(lugar=="kitchen"){
    goal.x=kitchen[0];
    goal.y=kitchen[1];
    goal.z=0;
  }
  if(lugar=="bedroom"){
    goal.x=bedroom[0];
    goal.y=bedroom[1];
    goal.z=0;
  }
  if(lugar=="living room"){
    goal.x=living_room[0];
    goal.y=living_room[1];
    goal.z=0;
  }
  pub_goal.publish(goal);
  ros::spinOnce();
  ROS_INFO("%f,%f,%f", goal.x, goal.y, goal.z);
  return BT::NodeStatus::RUNNING;
}

BT::PortsList navegacion::providedPorts()
{
    return { BT::InputPort<std::string>("getpos") };
}

}  // namespace behavior_trees
