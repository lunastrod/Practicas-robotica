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
    bool esperando=true;
    bool hablando=false;

};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_SALUDA_H
