#include <string>

#include "behavior_trees/cogebolsa.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

cogebolsa::cogebolsa(const std::string& name): BT::ActionNodeBase(name, {})
{
  sub_bolsa = n.subscribe("/bolsa_elegida",1,&cogebolsa::bolsa_callback, this);
  pub_goal=n.advertise<geometry_msgs::Point>("/navigator/goals",1);
}

void cogebolsa::bolsa_callback(const std_msgs::String& msg){
  bolsa=msg.data.c_str();
  ROS_INFO("eleccion: %s",bolsa.c_str());
  esperando=false;
  navegando=true;
}

void cogebolsa::halt()
{
  ROS_INFO("cogebolsa halt");
}

BT::NodeStatus cogebolsa::tick()
{
  if(esperando){
    ROS_INFO("esperando a la eleccion de la bolsa");
    return BT::NodeStatus::RUNNING;
  }
  if(buscando){
    ROS_INFO("buscando %s",bolsa.c_str());
    return BT::NodeStatus::RUNNING;
  }
  if(navegando){//TODO: navigation y darknet
    ROS_INFO("navegando");
    navegando=false;//TODO: temporal
    return BT::NodeStatus::RUNNING;
  }
  ROS_INFO("bolsa recogida\n");
  return BT::NodeStatus::SUCCESS;

}

}  // namespace behavior_trees
