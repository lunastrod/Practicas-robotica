#include "behavior_trees/go.h"
#include "behavior_trees/turn.h"

#include "ros/ros.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/package.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "behavior_tree");
  ros::NodeHandle n;

  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<behavior_trees::go>("go");
  factory.registerNodeType<behavior_trees::turn>("turn");

  std::string pkgpath = ros::package::getPath("practica7-behavior");
  std::string xml_file = pkgpath + "/trees/tree1.xml";

  BT::Tree tree = factory.createTreeFromFile(xml_file);

  ros::Rate loop_rate(5);

  int count = 0;

  while (ros::ok())
  {
    tree.root_node->executeTick() == BT::NodeStatus::SUCCESS;

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
