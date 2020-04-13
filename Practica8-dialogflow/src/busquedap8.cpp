#include "stdio.h"

#include "ros/ros.h"
#include <tf/transform_listener.h>
#include "sensor_msgs/CameraInfo.h"

#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_field_conversion.h>

#include "darknet_ros_msgs/BoundingBoxes.h"
#include <geometry_msgs/Point.h>
#include "std_msgs/Bool.h"
#include "sensor_msgs/PointCloud2.h"
#include "geometry_msgs/PointStamped.h"

#include "tf2/transform_datatypes.h"
#include "tf2/LinearMath/Transform.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/convert.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "servicios/busqueda.h"


class camara{
public:
  camara(){
    ros::NodeHandle n_;
    sub_objetos_ = n_.subscribe("/darknet_ros/bounding_boxes", 1, &camara::boxesCallBack, this);
    sub_point_cloud_ = n_.subscribe("/camera/depth/points",1,&camara::pointcloudCallBack,this);
  }
  void boxesCallBack(const darknet_ros_msgs::BoundingBoxes& msg){
    ROS_INFO("boxes callback");
    objeto_detectado_ = false;
    //TODO: solo comprueba el primer objeto de bounding_boxes
    if(!msg.bounding_boxes[0].Class.compare(tipo_objeto)){
      ROS_INFO("boxes coincide");
      centrox = (msg.bounding_boxes[0].xmin + msg.bounding_boxes[0].xmax) / 2;
      centroy = (msg.bounding_boxes[0].ymin + msg.bounding_boxes[0].ymax) / 2;
      objeto_detectado_ = true;
      //ROS_INFO("objeto detectado en (%d,%d)\n",centrox,centroy);
    }
  }
  void pointcloudCallBack(const sensor_msgs::PointCloud2& msg){
    camara3d=msg;
  }

  geometry_msgs::TransformStamped generate_object(geometry_msgs::Point& p){
    geometry_msgs::PointStamped point_in_camera_frame;
    geometry_msgs::Point p_ordenado;
    p_ordenado.x=p.z;
    p_ordenado.y=-p.x;
    p_ordenado.z=-p.y;

    point_in_camera_frame.point=p_ordenado;
    point_in_camera_frame.header.frame_id="camera_depth_frame";
    point_in_camera_frame.header.stamp = ros::Time::now();

    geometry_msgs::PointStamped point_in_map_frame;
    try{
      ros::Time now = ros::Time::now();
      tf_listener.waitForTransform("/map", "/camera_depth_frame" ,now, ros::Duration(3.0));
      tf_listener.transformPoint("/map", point_in_camera_frame, point_in_map_frame);
    }
    catch(...){
      point_in_map_frame.point.x= 0;
      point_in_map_frame.point.y= 0;
      point_in_map_frame.point.z= 0;
    }

    point_in_map_frame.header.frame_id="map";
    point_in_map_frame.header.stamp = ros::Time::now();

    ROS_INFO("camera:(%f,%f,%f)\n map:(%f,%f,%f)\n\n",point_in_camera_frame.point.x,point_in_camera_frame.point.y,point_in_camera_frame.point.z,point_in_map_frame.point.x,point_in_map_frame.point.y,point_in_map_frame.point.z);

    p.x=point_in_camera_frame.point.x;
    p.y=point_in_camera_frame.point.y;
    p.z=point_in_camera_frame.point.z;

    geometry_msgs::Transform transformada;
    geometry_msgs::Vector3 v;
    v.x= point_in_map_frame.point.x;
    v.y= point_in_map_frame.point.y;
    v.z= point_in_map_frame.point.z;
    transformada.translation=v;
    geometry_msgs::Quaternion q;
    q.x=0;
    q.y=0;
    q.z=0;
    q.w=1;
    transformada.rotation=q;

    geometry_msgs::TransformStamped object;
    object.child_frame_id = "object";//el nombre de la transformada
    object.transform=transformada;
    object.header.frame_id="map";
    object.header.stamp = ros::Time::now();

    return object;
  }

  bool service_function(servicios::busqueda::Request &req, servicios::busqueda::Response &res)
  {
    res.found.data=false;
    tipo_objeto=req.object.data;
    if(objeto_detectado_){
      geometry_msgs::Point p;
      pixelTo3DPoint(camara3d,centrox,centroy,p);
      ROS_INFO("point:(%f,%f,%f)\n", p.x, p.y, p.z);
      geometry_msgs::TransformStamped obj = generate_object(p);
      transform_broadcaster_.sendTransform(obj);

      res.position.x=p.x;
      res.position.y=p.y;
      res.position.z=p.z;
      res.found.data=true;
      
      objeto_detectado_=false;
    }
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

  int centrox;
  int centroy;
  bool objeto_detectado_ = false;
  std::string tipo_objeto= "";
  darknet_ros_msgs::BoundingBoxes boxes_darknet;
  sensor_msgs::PointCloud2 camara3d;
  ros::Subscriber sub_objetos_;
  tf::TransformListener tf_listener;
  ros::Subscriber sub_point_cloud_;
  tf2_ros::TransformBroadcaster transform_broadcaster_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "busquedap6");
  ros::NodeHandle n;

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
