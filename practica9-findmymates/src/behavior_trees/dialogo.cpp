#include <string>
#include "ros/ros.h"

#include "behavior_trees/dialogo.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ejemploDF.h"
#include <sound_play/sound_play.h>
#include <unistd.h>

#include <sstream>

void sleepok(int t, ros::NodeHandle &nh)
{
  if (nh.ok())
      sleep(t);
}


namespace behavior_trees
{

dialogo::dialogo(const std::string& name, const BT::NodeConfiguration& config)
  : ActionNodeBase(name, config)
{

}


void dialogo::halt()
{
  ROS_INFO("dialogo halt");
}

BT::NodeStatus dialogo::tick()
{
  gb_dialog::ExampleDF forwarder;
  std::string respuesta;
  //std::string nombre;
  //std::string color;
  std::string param_name;
  std::string str;
  sound_play::SoundClient sc;
  ros::NodeHandle nh;

  if(esperando){
    if(!nombre_conseguido){
      sc.say("Hello. Whats your name?");
      sleepok(2, nh);
      ROS_INFO("[Robot]: Hello. Whats your name?");
      forwarder.setintent("dialogo-nombre");
      //ROS_INFO("esperando un nombre");

      forwarder.listen();
      str = forwarder.getintentfound();
      respuesta = forwarder.getresponse();
      param_name = forwarder.getparamname();

      ROS_INFO("[Robot]: Nice to meet you,  %s\n", param_name.c_str());
      sc.say("Nice to meet you,  %s\n", param_name.c_str());
      if(!str.compare("dialogo-nombre")){
        if(!param_name.compare("given-name")){
          msg_nombre = forwarder.getobject();
          setOutput("personname", msg_nombre );
          ROS_INFO("[Robot]: nombre %s\n", msg_nombre.c_str());
          if(!msg_nombre.compare(""))
            return BT::NodeStatus::RUNNING;
          nombre_conseguido = true;
        }
      }
    }
    if(!color_conseguido){
      sc.say("I need to know the color of your shirt.");
      sleepok(1, nh);
      ROS_INFO("[Robot]: I need to know the color of your shirt.");
      forwarder.setintent("dialogo-color");
      forwarder.listen();
      str = forwarder.getintentfound();
      respuesta = forwarder.getresponse();
      param_name = forwarder.getparamname();
      if(!str.compare("dialogo-color")){
        if(!param_name.compare("color")){
          msg_color = forwarder.getobject();
          setOutput("color", msg_color );
          //ROS_INFO("[Robot]: color %s\n", msg_color.c_str());
          color_conseguido = true;
          esperando=false;//TODO:temporal
        }
      }
    }
    return BT::NodeStatus::RUNNING;
  }
  if(hablando){//TODO: dialog flow intent

    //ROS_INFO("hablando");
    return BT::NodeStatus::RUNNING;
  }


//  ROS_INFO("[Robot]: objeto %s", objeto.c_str());


  ros::spinOnce();
  //ROS_INFO("lugar elegido: %s\n",msg_lugar.data.c_str());
  nombre_conseguido = false;
  color_conseguido = false;
  esperando=true;
  hablando=false;
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList dialogo::providedPorts()
{
    return {
      BT::OutputPort<std::string>("color"),
      BT::OutputPort<std::string>("personname")
    };
}

}  // namespace behavior_trees
