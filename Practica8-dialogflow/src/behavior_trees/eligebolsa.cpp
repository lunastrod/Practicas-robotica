#include <string>

#include "behavior_trees/eligebolsa.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

#include "std_msgs/String.h"
#include <sstream>

namespace behavior_trees
{

eligebolsa::eligebolsa(const std::string& name): BT::ActionNodeBase(name, {})
{
  pub_bolsa=n.advertise<std_msgs::String>("/bolsa_elegida",1);
}

void eligebolsa::halt()
{
  ROS_INFO("eligebolsa halt");
}

BT::NodeStatus eligebolsa::tick()
{
  if(esperando){
    ROS_INFO("esperando a la eleccion de la bolsa");
    esperando=false;//TODO:temporal
    return BT::NodeStatus::RUNNING;
  }
  if(hablando){//TODO: dialog flow intent
    ROS_INFO("hablando");
    return BT::NodeStatus::RUNNING;
  }
  std::string bolsa;
  bolsa="pelota";//TODO:lo que tiene que escribir dialogflow y leerá darknet

  msg_bolsa.data = bolsa;
  pub_bolsa.publish(msg_bolsa);
  ros::spinOnce();
  ROS_INFO("bolsa elegida: %s\n",msg_bolsa.data.c_str());
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
