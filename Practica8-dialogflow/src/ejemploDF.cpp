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
class ExampleDF: public DialogInterface
{
  public:
    ExampleDF(): nh_()
    {
      this->registerCallback(std::bind(&ExampleDF::noIntentCB, this, ph::_1));
      this->registerCallback(
        std::bind(&ExampleDF::welcomeIntentCB, this, ph::_1),
        "Default Welcome Intent");
    }

    void noIntentCB(dialogflow_ros_msgs::DialogflowResult result)
    {
      ROS_INFO("[ExampleDF] noIntentCB: intent [%s]", result.intent.c_str());
      //ROS_INFO("[ExampleDF] noIntentCB: param [%s]", result.parameters.value[0].c_str());
    }

    void welcomeIntentCB(dialogflow_ros_msgs::DialogflowResult result)
    {
      ROS_INFO("[ExampleDF] welcomeIntentCB: intent [%s]", result.intent.c_str());
      speak(result.fulfillment_text);
    }

  private:
    ros::NodeHandle nh_;
};
}  // namespace gb_dialog

int main(int argc, char** argv)
{
  ros::init(argc, argv, "example_df_node");
  gb_dialog::ExampleDF forwarder;
  forwarder.listen();
  ros::spin();
  return 0;
}