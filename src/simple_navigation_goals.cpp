#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  move_base_msgs::MoveBaseGoal goal2;
  move_base_msgs::MoveBaseGoal goal3;
  move_base_msgs::MoveBaseGoal goal4;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = 1.4;
  goal.target_pose.pose.position.y = 0.3;
  goal.target_pose.pose.orientation.w = 0.5;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();    //wait for the first goal to finish
 
  //we'll send a goal to the robot to move 1.1 meter upward
  goal2.target_pose.header.frame_id = "map";
  goal2.target_pose.header.stamp = ros::Time::now();

  goal2.target_pose.pose.position.x = 1.4;
  goal2.target_pose.pose.position.y = 1.4;
  goal2.target_pose.pose.orientation.w = 0.5;

  ROS_INFO("Sending goal2");
  ac.sendGoal(goal2);

  ac.waitForResult();    //wait for the second goal to finish

  //we'll send a goal to the robot to move 1.1 meter to the left
  goal3.target_pose.header.frame_id = "map";
  goal3.target_pose.header.stamp = ros::Time::now();

  goal3.target_pose.pose.position.x = 0.3;
  goal3.target_pose.pose.position.y = 1.4;
  goal3.target_pose.pose.orientation.w = 0.5;

  ROS_INFO("Sending goal3");
  ac.sendGoal(goal3);

  ac.waitForResult();    //wait for the third goal to finish

  //we'll send a goal to the robot to move back to the origin
  goal4.target_pose.header.frame_id = "map";
  goal4.target_pose.header.stamp = ros::Time::now();

  goal4.target_pose.pose.position.x = 0.3;
  goal4.target_pose.pose.position.y = 0.3;
  goal4.target_pose.pose.orientation.w = 0.5;

  ROS_INFO("Sending goal4");
  ac.sendGoal(goal4);

  ac.waitForResult();    //wait for the fourth goal to finish
  /*
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1.1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1.1 meter for some reason");
  */
  return 0;
}

