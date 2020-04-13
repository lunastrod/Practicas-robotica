#include <string>

#include "behavior_trees/siguepersona.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

siguepersona::siguepersona(const std::string& name): BT::ActionNodeBase(name, {})
{
  pub_goal=n.advertise<geometry_msgs::Point>("/navigator/goals",1);
  sub_running = n.subscribe("/navigator/isrunning",1,&siguepersona::running_callback, this);
  goal.x=-4.1;
  goal.y=3.2;
  goal.z=0;
}

void siguepersona::halt()
{
  ROS_INFO("siguepersona halt");
}

void siguepersona::running_callback(const std_msgs::Bool& running){
  if(navegando && !running.data){
    ROS_INFO("he llegado a la persona\n");
    navegando=false;
    hablando=true;
  }
}

BT::NodeStatus siguepersona::tick()
{
  if(hablando){
    ROS_INFO("iniciando despedida");
    hablando=false;//TODO:temp
    return BT::NodeStatus::RUNNING;
  }
  if(buscando){
    ROS_INFO("buscando personas");
    buscando=false;//TODO:temp
    navegando=true;
    return BT::NodeStatus::RUNNING;
  }
  if(navegando){
    if(!goalsent){
      ROS_INFO("navegando a persona en la posicion:");//TODO:posicion
      pub_goal.publish(goal);
      goalsent=true;
    }
    return BT::NodeStatus::RUNNING;
  }
  ROS_INFO("despedida completada\n");
  return BT::NodeStatus::SUCCESS;

}

}  // namespace behavior_trees
