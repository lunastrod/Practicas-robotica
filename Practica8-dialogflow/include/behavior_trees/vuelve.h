#ifndef BEHAVIOR_TREES_VUELVE_H
#define BEHAVIOR_TREES_VUELVE_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Bool.h"

namespace behavior_trees
{

class vuelve : public BT::ActionNodeBase
{
  public:
    explicit vuelve(const std::string& name);
    void running_callback(const std_msgs::Bool& running);
    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Publisher pub_goal;
    ros::Subscriber sub_running;
    geometry_msgs::Point goal;

    bool navegando=true;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_VUELVE_H
