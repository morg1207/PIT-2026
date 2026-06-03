#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"

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
  ros::Subscriber pose_sub = n.subscribe("/turtle1/pose", 1, poseCallback);

  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);

  ros::Rate loop_rate(20);

  // mensaje
  geometry_msgs::Twist cmd_vel_msg;
  cmd_vel_msg.angular.z = 0.5;
  cmd_vel_msg.linear.x = 0.5;

  while(ros::ok()){
    cmd_vel_pub.publish(cmd_vel_msg);
    
    ROS_INFO("Publicando mensajes");
    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
