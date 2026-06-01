#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
  // Inicializando el nodo
  ros::init(argc, argv, "publicador");
  // Manejador de nodos
  ros::NodeHandle n;
  // Creo el enlace de mi publicador por mi nodo a través del manejador de nodos
  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
  // Creo el mensaje a publicar
  geometry_msgs::Twist cmd_vel_msg;
  // Edito el mensaje a publicar
  cmd_vel_msg.linear.x = 0.5;
  cmd_vel_msg.angular.z = 0.0;
  // Publico el mensaje en el tópico /turtle1/cmd_vel
  ros::Duration(1.0).sleep();
  cmd_vel_pub.publish(cmd_vel_msg);
  cmd_vel_pub.publish(cmd_vel_msg);
  cmd_vel_pub.publish(cmd_vel_msg);
  ros::Duration(1.0).sleep();
  // Frecuencia de publicación
  return 0;
}