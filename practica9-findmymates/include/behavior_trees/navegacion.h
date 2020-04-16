#ifndef BEHAVIOR_TREES_NAVEGACION_H
#define BEHAVIOR_TREES_NAVEGACION_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

namespace behavior_trees
{

class navegacion : public BT::ActionNodeBase
{
  public:
    explicit navegacion(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
    int counter_;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_NAVEGACION_H
