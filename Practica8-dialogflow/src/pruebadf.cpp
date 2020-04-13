#include <gb_dialog/DialogInterface.h>
#include <string>

/*
string action
string query_text //lo que has dicho
string fulfillment_text //respuesta
dialogflow_ros_msgs/DialogflowParameter[] parameters
  string param_name //el nombre del parametro
  string[] value //lo que pides

dialogflow_ros_msgs/DialogflowContext[] contexts
  string name
  int32 lifespan_count
  dialogflow_ros_msgs/DialogflowParameter[] parameters
    string param_name
    string[] value
string intent


*/


namespace ph = std::placeholders;

namespace gb_dialog
{
class pruebadf: public DialogInterface
{
  public:
    pruebadf(): nh_()
    {
      this->registerCallback(std::bind(&pruebadf::noIntentCB, this, ph::_1));
      this->registerCallback(
        std::bind(&pruebadf::welcomeIntentCB, this, ph::_1),
        "Default Welcome Intent");
    }

    void noIntentCB(dialogflow_ros_msgs::DialogflowResult result)
    {
      //ROS_INFO("[%s  %s   %d]", result.intent.c_str(), intent.c_str(),result.intent.compare(intent));
      //ROS_INFO("[ExampleDF] noIntentCB: intent [%s]", result.intent.c_str());
      //ROS_INFO("[ExampleDF] noIntentCB: response en callback [%s]", respuesta.c_str());
      intent_encontrado = result.intent.c_str();
      respuesta = result.fulfillment_text.c_str();
      ROS_INFO("[ExampleDF] noIntentCB: response en callback [%s]", respuesta.c_str());
        //ROS_INFO("%s",result.parameters[0].param_name.c_str());
      if(!result.intent.compare(intent_buscado)){
        objeto = result.parameters[0].value[0];
      }
      else{
        objeto = "Null";
      }
      //ROS_INFO("[ExampleDF] noIntentCB: param [%s]", objeto.c_str());
    }

    void welcomeIntentCB(dialogflow_ros_msgs::DialogflowResult result)
    {
      //ROS_INFO("[ExampleDF] welcomeIntentCB: intent [%s]", result.intent.c_str());
      speak(result.fulfillment_text);
    }

    void setintent(std::string str){
      intent_buscado = str;
    }

    std::string getintentfound(){
      ros::spinOnce();
      std::string result = intent_encontrado;
      intent_encontrado = "Null";
      intent_actualizado = false;
      return result;
    }

    std::string getobject(){
      ros::spinOnce();
      std::string result = objeto;
      objeto = "Null";
      objeto_actualizado = false;
      return result;
    }

    std::string getresponse(){
      ros::spinOnce();
      //ROS_INFO("[ExampleDF] noIntentCB: response en getter [%s]", respuesta.c_str());
      std::string result = respuesta;
      //ROS_INFO("[ExampleDF] getresponse [%s]", respuesta.c_str());
      respuesta = "Null";
      response_actualizado = false;
      return result;
    }

  private:
    ros::NodeHandle nh_;
    std::string intent_buscado = "Null";
    std::string intent_encontrado = "Null";
    //std::string intent_encontrado = "Carry my luggage";
    std::string objeto = "Null";
    std::string respuesta = "Null";
    bool intent_actualizado = false;
    bool response_actualizado = false;
    bool objeto_actualizado = false;
  };
}  // namespace gb_dialog

int main(int argc, char** argv)
{
  ros::init(argc, argv, "example_df_node");
  gb_dialog::pruebadf forwarder;
  forwarder.listen();
  //std::string respuesta = forwarder.getresponse();

  ros::spinOnce();
  std::string respuesta = forwarder.getresponse();
  ROS_INFO("[Robot]: %s", respuesta.c_str());
  return 0;
}
