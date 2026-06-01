#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
float pos_x = 0.0;
float pos_y = 0.0;

void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
  pos_x = msg->x;  
  pos_y = msg->y;  
  ROS_INFO("Posición en [ x: %.3f  y: %.3f]",msg->x,msg->y);
}

int main(int argc, char **argv)
{
  // Inicializando el nodo
  ros::init(argc, argv, "nodo_suscriptor");
  ROS_INFO("Nodo inicializado");
  // Manejador de nodos
  ros::NodeHandle n;

  // Creo el obejeto suscriptor
  ros::Subscriber pose_sub = n.subscribe("/turtle1/pose", 10, poseCallback);

  ros::spin();

  return 0;
}