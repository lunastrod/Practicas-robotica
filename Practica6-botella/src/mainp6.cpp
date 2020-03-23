#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include "softarq_msgs/Distance.h"

#include "tf2/transform_datatypes.h"
#include "tf2/LinearMath/Transform.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/convert.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"

#include <time.h>
#include <math.h>



int main(int argc, char **argv)
{
  ros::init(argc, argv, "navp6");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<softarq_msgs::Distance>("detecta_obj");
  softarq_msgs::Distance srv;

  ros::Rate loop_rate(5);
  while (ros::ok())
  {
    client.call(srv);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
