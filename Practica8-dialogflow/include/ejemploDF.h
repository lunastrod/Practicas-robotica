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
      /*{
        this->registerCallback(std::bind(&ExampleDF::noIntentCB, this, ph::_1));
        this->registerCallback(
          std::bind(&ExampleDF::welcomeIntentCB, this, ph::_1),
          "Default Welcome Intent");
      }*/
      void noIntentCB(dialogflow_ros_msgs::DialogflowResult result);
      void welcomeIntentCB(dialogflow_ros_msgs::DialogflowResult result);
      void setintent(std::string str);
      std::string getintentfound();
      std::string getobject();
      std::string getresponse();

    private:
      std::string intent_buscado = "Null";
      std::string intent_encontrado = "Null";
      //std::string intent_encontrado = "Carry my luggage";
      std::string objeto = "Null";
      std::string respuesta = "Null";
    };
}  // namespace gb_dialog
#endif
