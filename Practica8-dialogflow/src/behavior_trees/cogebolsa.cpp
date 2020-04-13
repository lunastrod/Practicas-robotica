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
  sub_running = n.subscribe("/navigator/isrunning",1,&cogebolsa::running_callback, this);
  srv_busqueda = n.serviceClient<servicios::busqueda>("detecta_obj");
  goal.x=-2.1;
  goal.y=0.2;
  goal.z=0;
}

void cogebolsa::bolsa_callback(const std_msgs::String& msg){
  bolsa=msg.data.c_str();
  ROS_INFO("eleccion: %s",bolsa.c_str());
  esperando=false;
  buscando=true;
}

void cogebolsa::running_callback(const std_msgs::Bool& running){
  if(navegando && !running.data){
    ROS_INFO("he llegado a la bolsa\n");
    navegando=false;
  }
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
    //TODO:
    buscando=false;
    navegando=true;
    return BT::NodeStatus::RUNNING;
  }
  if(navegando){//TODO: navigation y darknet
    if(!goalsent){
      ROS_INFO("navegando");
      pub_goal.publish(goal);
      goalsent=true;
    }
    return BT::NodeStatus::RUNNING;
  }
  ROS_INFO("bolsa recogida\n");
  return BT::NodeStatus::SUCCESS;

}

}  // namespace behavior_trees
