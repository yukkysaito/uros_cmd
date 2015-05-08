#include "ros/ros.h"
#include "turtlesim/Velocity.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_cmd");
    ros::NodeHandle n;

    ros::Publisher cmd_pub = n.advertise<turtlesim::Velocity>("/turtle1/command_velocity", 1);
    ros::Rate loop_rate(10); //10Hz

    float angular, linear;
    char buf[32];
    printf("input angle(float): ");
    fgets(buf, sizeof(buf), stdin);
    buf[strlen(buf) - 1] = '\0';
    angular = atof(buf);
    printf("input line(float): ");
    fgets(buf, sizeof(buf), stdin);
    buf[strlen(buf) - 1] = '\0';
    linear = atof(buf);

    printf("publish cycle time : 100ms\n");
    while (ros::ok())
    {
        turtlesim::Velocity msg;
        msg.angular = angular;
        msg.linear = linear;
        cmd_pub.publish(msg);
        ROS_INFO("linear:%f, angular:%f", msg.linear, msg.angular);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
