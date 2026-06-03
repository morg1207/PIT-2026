#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
float pos_x = 0.0;
float pos_y = 0.0;

void poseTurtleCallback(const turtlesim::Pose::ConstPtr& msg)
{
  pos_x = msg->x;  
  pos_y = msg->y;  
  ROS_INFO("Posición de turtle1 en [ x: %.3f  y: %.3f]",msg->x,msg->y);
}

void posePit2026Callback(const turtlesim::Pose::ConstPtr& msg)
{
  pos_x = msg->x;  
  pos_y = msg->y;  
  ROS_INFO("Posición de pit2026 en [ x: %.3f  y: %.3f]",msg->x,msg->y);
}



int main(int argc, char **argv)
{
  // Inicializando el nodo
  ros::init(argc, argv, "nodo_suscriptor");
  ROS_INFO("Nodo inicializado");
  // Manejador de nodos
  ros::NodeHandle n;

  // Creo el objeto suscriptor y publicador
  ros::Subscriber pose_turtle_sub = n.subscribe("/turtle1/pose", 1, poseTurtleCallback);
  ros::Subscriber pose_pit2026_sub = n.subscribe("/pit2026/pose", 1, posePit2026Callback);

  ros::Publisher cmd_vel_turtle_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
  ros::Publisher cmd_vel_pit2026_pub = n.advertise<geometry_msgs::Twist>("/pit2026/cmd_vel",10);
  
  // Cliente de servicio
  ros::ServiceClient spawn_client = n.serviceClient<turtlesim::Spawn>("spawn");
  turtlesim::Spawn spawn_srv;
  spawn_srv.request.x = 2.0;
  spawn_srv.request.y = 2.0;
  spawn_srv.request.theta = 1.57;
  spawn_srv.request.name = "pit2026";
  // Llamando al servicio
  if(spawn_client.call(spawn_srv))
    ROS_INFO("Tortuga creada: %s",spawn_srv.request.name.c_str());
  else
    ROS_ERROR("Fallo al llamar /spawn");



  // Envio comandos de velocidad
  ros::Rate loop_rate(20);
  // mensaje
  geometry_msgs::Twist cmd_vel_msg;

  while(ros::ok()){

    cmd_vel_msg.angular.z = 0.5;
    cmd_vel_msg.linear.x = 0.5;
    cmd_vel_turtle_pub.publish(cmd_vel_msg);
    cmd_vel_msg.angular.z = 1.0;
    cmd_vel_msg.linear.x = 1.0;
    cmd_vel_pit2026_pub.publish(cmd_vel_msg);
    ROS_INFO("Publicando mensajes");
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}