#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include <std_msgs/Int8.h>
#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "geometry_msgs/PoseStamped.h"


class Navigator
{
  public:
    Navigator(ros::NodeHandle& nh) : nh_(nh), action_client_("/move_base", false), goal_sent_(false)
    {
      navigator_goals_sub = nh_.subscribe("navigator_goals", 1, &Navigator::goalscallback, this);
      POSITION[0].x=0;
      POSITION[0].y=0;
      POSITION[0].z=0;

      POSITION[1].x=10;
      POSITION[1].y=0;
      POSITION[1].z=0;

      POSITION[2].x=0;
      POSITION[2].y=10;
      POSITION[2].z=0;

      POSITION[3].x=10;
      POSITION[3].y=10;
      POSITION[3].z=0;
    }

    void goalscallback(const std_msgs::Int8& msg){
      if(msg.data<NUMBER_GOALS){
        current_goal=msg.data;
      }
    }

    void step()
    {
      gotogoal(current_goal);
      if (goal_sent_)
      {
        bool finished_before_timeout = action_client_.waitForResult(ros::Duration(0.5));
        actionlib::SimpleClientGoalState state = action_client_.getState();
        if (finished_before_timeout)
        {
          actionlib::SimpleClientGoalState state = action_client_.getState();
          if (state == actionlib::SimpleClientGoalState::SUCCEEDED)
            ROS_INFO("[navigate_to_wp] Goal Reached!");
          else
            ROS_INFO("[navigate_to_wp] Something bad happened!");
          goal_sent_ = false;
        }
      }
    }

    void gotogoal(int n)
    {
      if(!goal_sent_){
        geometry_msgs::PoseStamped goal_pose_;
        goal_pose_.pose.position=POSITION[0];
        goal_pose_.pose.orientation.x=0;
        goal_pose_.pose.orientation.y=0;
        goal_pose_.pose.orientation.z=0;
        goal_pose_.pose.orientation.w=1;

        ROS_INFO("[navigate_to_wp] Commanding to (%f %f)", goal_pose_.pose.position.x, goal_pose_.pose.position.y);

        move_base_msgs::MoveBaseGoal goal;
        goal.target_pose = goal_pose_;
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        action_client_.sendGoal(goal);
        goal_sent_ = true;
      }
    }

  private:
    ros::NodeHandle nh_;
    ros::Subscriber wp_sub_;
    ros::Subscriber navigator_goals_sub;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;

    static const int NUMBER_GOALS=4;
    bool goal_sent_;
    int current_goal;

    geometry_msgs::Point POSITION[NUMBER_GOALS];


};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "navp6");
  ros::NodeHandle nh("~");
  Navigator navigator(nh);
  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    navigator.step();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
