#include "stdio.h"

#include "ros/ros.h"
//#include <tf/transform_listener.h>
//#include "actionlib/client/simple_action_server.h"
#include "sensor_msgs/CameraInfo.h"

#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_field_conversion.h>

#include "darknet_ros_msgs/BoundingBoxes.h"
#include <geometry_msgs/Point.h>
#include "sensor_msgs/PointCloud2.h"

#include "tf2/transform_datatypes.h"
#include "tf2/LinearMath/Transform.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/convert.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "softarq_msgs/Distance.h"

///camera/depth_registered/points
//Type: sensor_msgs/PointCloud2


class camara{
public:
  camara(){
    ros::NodeHandle n_;
    sub_objetos_ = n_.subscribe("/darknet_ros/bounding_boxes", 1, &camara::boxesCallBack, this);
    //sub_camera_ = n_.subscribe("/camera/rgb/camera_info", 1, &camara::cameraCallBack, this);
    sub_point_cloud_ = n_.subscribe("/camera/depth/points",1,&camara::pointcloudCallBack,this);
  }
  void boxesCallBack(const darknet_ros_msgs::BoundingBoxes& msg){
    if(service_state){
      objeto_detectado_ = false;
      //TODO: solo comprueba el primer objeto de bounding_boxes
      if(!msg.bounding_boxes[0].Class.compare(tipo_objeto)){
        centrox = (msg.bounding_boxes[0].xmin + msg.bounding_boxes[0].xmax) / 2;
        centroy = (msg.bounding_boxes[0].ymin + msg.bounding_boxes[0].ymax) / 2;
        objeto_detectado_ = true;
        //ROS_INFO("objeto detectado en (%d,%d)\n",centrox,centroy);
      }
    }
  }
  void pointcloudCallBack(const sensor_msgs::PointCloud2& msg){
    if(objeto_detectado_ && service_state){
      geometry_msgs::Point p;
      pixelTo3DPoint(msg,centrox,centroy,p);
      ROS_INFO("point:(%f,%f,%f)\n", p.x, p.y, p.z);
      geometry_msgs::TransformStamped obj = generate_object(p);
      transform_broadcaster_.sendTransform(obj);

    }
    service_state = false;
  }
  geometry_msgs::TransformStamped generate_object(geometry_msgs::Point p)
    {
      /*
      devuelve una transformada al punto p (suponiendo que viene de la camara)
      */
      tf2::Stamped<tf2::Transform> object;
      object.frame_id_ = "camera_depth_frame";//el origen de coordenadas del punto
      //object.frame_id_ = "base_footprint";
      object.stamp_ = ros::Time::now();

      object.setOrigin(tf2::Vector3(p.z, -p.x, p.y));//ni idea de por qué están así
      tf2::Quaternion q;
      q.setRPY(0.0, 0.0, 0.0);
      object.setRotation(q);

      geometry_msgs::TransformStamped object_msg = tf2::toMsg(object);
      object_msg.child_frame_id = "object";//el nombre de la transformada

      return object_msg;
    }

    bool service_function(softarq_msgs::Distance::Request  &req,
         softarq_msgs::Distance::Response &res){
      service_state = true;
      return true;
    }

private:
  void pixelTo3DPoint(const sensor_msgs::PointCloud2 &pCloud, const int u, const int v, geometry_msgs::Point &p)
    {
      /*
      https://answers.ros.org/question/191265/pointcloud2-access-data/
      Function to convert 2D pixel point to 3D point by extracting point
      from PointCloud2 corresponding to input pixel coordinate. This function
      can be used to get the X,Y,Z coordinates of a feature using an
      RGBD camera.
      */
      // get width and height of 2D point cloud data
      int width = pCloud.width;
      int height = pCloud.height;

      // Convert from u (column / width), v (row/height) to position in array
      // where X,Y,Z data starts
      int arrayPosition = v*pCloud.row_step + u*pCloud.point_step;

      // compute position in array where x,y,z data start
      int arrayPosX = arrayPosition + pCloud.fields[0].offset; // X has an offset of 0
      int arrayPosY = arrayPosition + pCloud.fields[1].offset; // Y has an offset of 4
      int arrayPosZ = arrayPosition + pCloud.fields[2].offset; // Z has an offset of 8

      float X = 0.0;
      float Y = 0.0;
      float Z = 0.0;

      memcpy(&X, &pCloud.data[arrayPosX], sizeof(float));
      memcpy(&Y, &pCloud.data[arrayPosY], sizeof(float));
      memcpy(&Z, &pCloud.data[arrayPosZ], sizeof(float));

     // put data into the point p
      p.x = X;
      p.y = Y;
      p.z = Z;

    }



  const std::string tipo_objeto = "sports ball";
  /*
  int image_width;
  int image_height;
  */
  int centrox;
  int centroy;
  bool service_state = false;
  bool objeto_detectado_ = false;
  ros::Subscriber sub_objetos_;
  //ros::Subscriber sub_camera_;
  ros::Subscriber sub_point_cloud_;
  tf2_ros::TransformBroadcaster transform_broadcaster_;
};

int main(int argc, char **argv)
{
  ros::NodeHandle n;
  ros::init(argc, argv, "busquedap6");

  camara cam;
  ros::ServiceServer service = n.advertiseService("detecta_obj", &camara::service_function, &cam);
  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
