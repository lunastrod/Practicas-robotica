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
    explicit busca(const std::string& name);

    void halt();
    BT::NodeStatus tick();
  private:
    ros::NodeHandle n;
    ros::Publisher pub_lugar;
    std_msgs::String msg_lugar;

    bool esperando=true;
    bool hablando=false;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_BUSCA_H
