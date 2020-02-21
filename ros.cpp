/*
 *  Project: ros_redirect
 *  File: ros.cpp
 *
 *  Date: 21.02.2020
 *  Author: Markovvn1
 */

#include "ros.hpp"
#include "net.hpp"

#include "time.hpp"

#include <cstdint>
#include <ctime>
#include <string>

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

ros::NodeHandle* n;
ros::Publisher publisher;
ros::Subscriber subscriber;

sensor_msgs::JointState msg;

void rosSendData(const char* data, int len)
{
	msg.position.push_back(len);
}

void rosSpin()
{
	ros::spin();
}

void rosCallback(const sensor_msgs::JointState& msg)
{
	netSendData((char*)&msg.position[0], 8);
}

void rosInitNode()
{
	// Используем время в микросекундах как сид случайности
	srand(getCTimeMicrosecond());
	int zero = 0;
	ros::init(zero, NULL, std::string("redirect_") + std::to_string(rand() % 1000000));
	n = new ros::NodeHandle;
}

void rosDeinitNode()
{
	delete n;
}

void rosInitPublisher(const char* name)
{
	rosInitNode();
	publisher = n->advertise<sensor_msgs::JointState>(name, 1);
}

void rosDeinitPublisher()
{
	rosDeinitNode();
}

void rosInitSubscriber(const char* name)
{
	rosInitNode();
	subscriber = n->subscribe(name, 1, rosCallback);
}

void rosDeinitSubscriber()
{
	rosDeinitNode();
}
