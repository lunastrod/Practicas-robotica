#ifndef BEHAVIOR_TREES_SALUDO_H
#define BEHAVIOR_TREES_SALUDO_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Bool.h"

namespace behavior_trees
{

class saludo : public BT::ActionNodeBase
{
  public:
    explicit saludo(const std::string& name);

    void running_callback(const std_msgs::Bool& running);

    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Publisher pub_goal;
    geometry_msgs::Point goal;
    ros::Subscriber sub_running;

    bool navegando=true;
    bool active=false;
    bool esperando=true;
    bool hablando=false;


};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_SALUDO_H
