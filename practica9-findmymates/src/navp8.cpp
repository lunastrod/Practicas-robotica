#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include <std_msgs/Int8.h>
#include <geometry_msgs/Point.h>
#include "std_msgs/Bool.h"
#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "geometry_msgs/PoseStamped.h"

#include <sensor_msgs/PointCloud2.h>

class Navigator
{
  public:
    Navigator(ros::NodeHandle& nh) : nh_(nh), action_client_("/move_base", false), goal_sent_(false)
    {
      navigator_running_pub = nh_.advertise<std_msgs::Bool>("/navigator/isrunning", 1);
      navigator_goals_sub = nh_.subscribe("/navigator/goals", 1, &Navigator::goalscallback, this);

    }

    void goalscallback(const geometry_msgs::Point& msg){
      if(!running.data){
        currentgoal=msg;
        //ROS_INFO("[navigate_to_wp] msg recieved, current goal: (%f,%f,%f)",currentgoal.x,currentgoal.y,currentgoal.z);
        goal_recieved_ = true;
      }
    }

    void step()
    {
      gotogoal();
      if (goal_sent_)
      {
        bool finished_before_timeout = action_client_.waitForResult(ros::Duration(0.5));
        actionlib::SimpleClientGoalState state = action_client_.getState();
        if (finished_before_timeout)
        {
          actionlib::SimpleClientGoalState state = action_client_.getState();
          if (state == actionlib::SimpleClientGoalState::SUCCEEDED){
            //ROS_INFO("[navigate_to_wp] Goal Reached!");
            running.data=false;
            navigator_running_pub.publish(running);
          }
          else
            running.data=false;
            navigator_running_pub.publish(running);
            //ROS_INFO("[navigate_to_wp] Something bad happened!");
          goal_sent_ = false;
        }
      }
    }

    void gotogoal()
    {
      if(goal_recieved_){
        geometry_msgs::PoseStamped goal_pose_;
        goal_pose_.pose.position=currentgoal;
        goal_pose_.pose.orientation.x=0;
        goal_pose_.pose.orientation.y=0;
        goal_pose_.pose.orientation.z=0;
        goal_pose_.pose.orientation.w=1;

        //ROS_INFO("[navigate_to_wp] Commanding to (%f %f)", goal_pose_.pose.position.x, goal_pose_.pose.position.y);

        move_base_msgs::MoveBaseGoal goal;
        goal.target_pose = goal_pose_;
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        action_client_.sendGoal(goal);
        goal_recieved_=false;
        goal_sent_ = true;
        running.data=true;
        navigator_running_pub.publish(running);
      }
    }

  private:
    ros::NodeHandle nh_;
    ros::Subscriber wp_sub_;
    ros::Subscriber navigator_goals_sub;
    ros::Publisher navigator_running_pub;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;
    std_msgs::Bool running;

    bool goal_sent_=false;
    bool goal_recieved_=false;

    geometry_msgs::Point currentgoal;


};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "navp6");
  ros::NodeHandle nh("~");
  Navigator navigator(nh);
  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    navigator.step();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
