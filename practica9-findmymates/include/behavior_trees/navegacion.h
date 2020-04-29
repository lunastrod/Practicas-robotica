#ifndef BEHAVIOR_TREES_NAVEGACION_H
#define BEHAVIOR_TREES_NAVEGACION_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Bool.h"

namespace behavior_trees
{

class navegacion : public BT::ActionNodeBase
{
  public:
    navegacion(const std::string& name, const BT::NodeConfiguration& config);

    static BT::PortsList providedPorts();
    void running_callback(const std_msgs::Bool& running);

    void halt() override;

    BT::NodeStatus tick() override;

  private:
    ros::NodeHandle n;
    ros::Publisher pub_goal;
    geometry_msgs::Point goal;
    ros::Publisher pub_vel_;
    ros::Subscriber sub_running;

    bool navegando=true;
    bool active=false;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_NAVEGACION_H
