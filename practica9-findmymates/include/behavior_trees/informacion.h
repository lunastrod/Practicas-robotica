#ifndef BEHAVIOR_TREES_INFORMACION_H
#define BEHAVIOR_TREES_INFORMACION_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "std_msgs/Bool.h"
#include "ros/ros.h"

#include <string>

namespace behavior_trees
{

class informacion : public BT::ActionNodeBase
{
  public:
    informacion(const std::string& name, const BT::NodeConfiguration& config);

    static BT::PortsList providedPorts();

    void halt() override;
    BT::NodeStatus tick() override;
  private:
    ros::Publisher stage_pub;
    ros::NodeHandle nh;
    std_msgs::Bool fin;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_INFORMACION_H
