#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#define W 13
#define P 3

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "lawn_mowing");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  int i = 0;
  move_base_msgs::MoveBaseGoal goal;
  float goal_arrays[W][P] = {{0.3048, 1.524, 0.5}, {0.9144, 1.524, 0.5}, {0.9144, 0.3048, 0.5}, 
				{1.524, 0.3048, 0.5}, {1.524, 3.9624, 0.5}, {2.1633, 3.9624, 0.5}, 
				{2.1633, 0.3048, 0.5}, {2.7432, 0.3048, 0.5}, {2.7432, 3.9624, 0.5}, 
				{3.3528, 3.9624, 0.5}, {3.3528, 1.524, 0.5}, {3.9624, 1.524, 0.5}, 
				{3.9624, 4.1148, 0.5} };

  while(i < W){
	goal.target_pose.header.frame_id = "map";
  	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = goal_arrays[i][0];
  	goal.target_pose.pose.position.y = goal_arrays[i][1];
  	goal.target_pose.pose.orientation.w = goal_arrays[i][2];
	
  	ROS_INFO("Sending goal");
  	ac.sendGoal(goal);

 	ac.waitForResult();
	
	//get next goal
	i++;

  }

  return 0;
}

