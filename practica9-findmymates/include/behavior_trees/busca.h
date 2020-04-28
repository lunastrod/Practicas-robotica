#ifndef BEHAVIOR_TREES_BUSCA_H
#define BEHAVIOR_TREES_BUSCA_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

#include "ros/ros.h"
#include "std_msgs/String.h"

namespace behavior_trees
{

class busca : public BT::ActionNodeBase
{
  public:
    busca(const std::string& name, const BT::NodeConfiguration& config);

    static BT::PortsList providedPorts();

    void halt() override;
    BT::NodeStatus tick() override;
  private:
    ros::NodeHandle n;

    bool esperando=true;
    bool hablando=false;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_BUSCA_H
