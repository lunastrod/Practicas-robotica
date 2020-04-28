#include <string>

#include "behavior_trees/informacion.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include <string>

#include "std_msgs/Bool.h"
#include "ejemploDF.h"
#include "ros/ros.h"
#include "sound_play/sound_play.h"

namespace behavior_trees
{

informacion::informacion(const std::string& name, const BT::NodeConfiguration& config)
  : ActionNodeBase(name, config)
{
  stage_pub = nh.advertise<std_msgs::Bool>("/find_my_mates/finished", 1);
}

void informacion::halt()
{
  ROS_INFO("informacion halt");
}

BT::NodeStatus informacion::tick()
{
  BT::Optional<std::string> color = getInput<std::string>("getcolor");
  if (!color)
  {
    throw BT::RuntimeError("missing required input [message]: ",
                         color.error() );
  }
  BT::Optional<std::string> name = getInput<std::string>("getpersonname");
  if (!name)
  {
    throw BT::RuntimeError("missing required input [message]: ",
                         name.error() );
  }

  std::cout << "Robot says: " << color.value() << std::endl;
  std::cout << "Robot says: " << name.value() << std::endl;

  ROS_INFO("informacion tick");
  //return BT::NodeStatus::RUNNING;
  sound_play::SoundClient sc;
  std::string info = "There is ";
  info = info + name.value();
  info = info + " and the shirt is ";
  info = info + color.value();
  sc.say(info);
  gb_dialog::ExampleDF forwarder;
  forwarder.setintent("Job is done");
  //forwarder.setintent("Default Welcome Intent");
  forwarder.listen();
  ros::spinOnce();
  std::string respuesta = forwarder.getresponse();
  std::string str = forwarder.getintentfound();

  if(!str.compare("Job is done")){
    ROS_INFO("[Robot]: %s", respuesta.c_str());
    fin.data = true;
    stage_pub.publish(fin);
  }
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList informacion::providedPorts()
{
    return {
      BT::InputPort<std::string>("getcolor"),
      BT::InputPort<std::string>("getpersonname")
    };
}

}  // namespace behavior_trees
