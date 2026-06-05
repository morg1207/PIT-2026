#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "std_srvs/Trigger.h"
#include "std_srvs/Empty.h"

ros::Publisher pub_cmd_vel;
ros::ServiceClient reset_client;

float pose_x = 0.0;
float pose_y = 0.0;
float pose_theta = 0.0;

bool flag_suscriptor=false;


double posicion_final=2.0;


void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
  if(!flag_suscriptor){
    return;
  }
  pose_x = msg->x;
  pose_y = msg->y;
  pose_theta = msg->theta;
  ROS_INFO("Posición actual: x=%.2f, y=%.2f, ángulo=%.2f", pose_x, pose_y, pose_theta);
}



bool parabolaCallbak(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res){

    flag_suscriptor = true;

    ROS_INFO("Recibida solicitud para dibujar parabola");
    // Cliente de servicio
    std_srvs::Empty reset_srv;
    // Llamando al servicio
    if(reset_client.call(reset_srv))
        ROS_INFO("Se reicnio turtle1");
    else
        ROS_ERROR("Fallo al llamar /reset");


    // Parámetros de la parábola (y = a*x^2)
    const double a = 0.2;
    const double x_start = 2.0;

    const double ganancia_angular = 1.5;
    const double velocidad_lineal = 1.0;

    geometry_msgs::Twist msg_cmd_vel;
    msg_cmd_vel.angular.z = 0.0;
    msg_cmd_vel.linear.x = 0.0;
    // Publicar cero primero para detener cualquier movimiento previo
    pub_cmd_vel.publish(msg_cmd_vel);

    ROS_INFO("Iniciando trayectoria parabolica...");


    ros::Rate rate(50); // 50 Hz
    while(ros::ok() && pose_x <= posicion_final){

        double pendiente = 2.0 * a * pose_x;
        double angulo_deseado = atan(pendiente);
        double error = angulo_deseado - pose_theta;

        msg_cmd_vel.angular.z = error*ganancia_angular;
        msg_cmd_vel.linear.x = 1.0;

        pub_cmd_vel.publish(msg_cmd_vel);

        ROS_INFO("Comando: velocidad=%.2f, angular=%.2f", 
             msg_cmd_vel.linear.x, msg_cmd_vel.angular.z);

       ros::spinOnce();      
       rate.sleep();

    }

    // Detener la tortuga al ficnalizar
    msg_cmd_vel.linear.x = 0.0;
    msg_cmd_vel.angular.z = 0.0;
    pub_cmd_vel.publish(msg_cmd_vel);

    // se ha concluido con la tarea del servicio
    res.success = true;
    res.message = "Trayectoria parabólica completada";

    ROS_INFO("Trayectoria parabólica completada");

  //reinicio variables
  flag_suscriptor =false;
  pose_x = 0.0;
  pose_y = 0.0;
  return true;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "sevidor_servicio_parabola");
  ros::NodeHandle n("~");

  // Publicador cmd_vel
  pub_cmd_vel = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
  // Cliente
  reset_client= n.serviceClient<std_srvs::Empty>("reset");

  // Suscriptor de pose
  ros::Subscriber pose_sub = n.subscribe("/turtle1/pose", 1, poseCallback);

  // Suscriptor de pose  
  ros::ServiceServer parabola_server = n.advertiseService("dibujar_parabola", parabolaCallbak);
  
  //Configuración inicial
  n.param<double>("posicion_final", posicion_final, 5.0);

  ROS_INFO("Posicion final de la parábola : %.3f", posicion_final);


  ROS_INFO("Servicio listo para recibir solicitudes del cliente.");

  
  ros::spin();

  return 0;
}