#ifndef BEHAVIOR_TREES_SALUDA_H
#define BEHAVIOR_TREES_SALUDA_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

#include "geometry_msgs/Point.h"

namespace behavior_trees
{

class saluda : public BT::ActionNodeBase
{
  public:
    explicit saluda(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
    geometry_msgs::Point inicio;//la posicion inicial TODO: es necesaria?

};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_SALUDA_H
