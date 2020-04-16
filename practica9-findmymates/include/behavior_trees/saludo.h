#ifndef BEHAVIOR_TREES_SALUDO_H
#define BEHAVIOR_TREES_SALUDO_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

namespace behavior_trees
{

class saludo : public BT::ActionNodeBase
{
  public:
    explicit saludo(const std::string& name);

    void halt();
    BT::NodeStatus tick();
  private:
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_SALUDO_H
