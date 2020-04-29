#ifndef DF_EJEMPLODF_H
#define DF_EJEMPLODF_H

#include <gb_dialog/DialogInterface.h>
#include <string>


namespace ph = std::placeholders;

namespace gb_dialog
{
  class ExampleDF: public DialogInterface
  {
    public:
      ExampleDF();
      void noIntentCB(dialogflow_ros_msgs::DialogflowResult result);
      void welcomeIntentCB(dialogflow_ros_msgs::DialogflowResult result);
      void setintent(std::string str);
      std::string getintentfound();
      std::string getobject();
      std::string getresponse();
      std::string getparamname();
      std::string gettext();


    private:
      ros::NodeHandle nh_;
      std::string intent_buscado;
      std::string intent_encontrado = "Null";
      std::string param_name = "Null";
      //std::string intent_encontrado = "Carry my luggage";
      std::string objeto = "Null";
      std::string respuesta = "Null";
      std::string reconocido = "Null";
    };
}  // namespace gb_dialog
#endif
