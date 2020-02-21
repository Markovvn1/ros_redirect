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
#include <exception>

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

ros::NodeHandle* n;
ros::Publisher publisher;
ros::Subscriber subscriber;

sensor_msgs::JointState msg;

void rosSendData(const char* data, int len)
{
	int shift = 0;

	// position
	msg.position.resize(*((int*)(data + shift)));
	shift += 4;
	memcpy(msg.position.data(), data + shift, msg.position.size() * 8);
	shift += msg.position.size() * 8;

	// velocity
	msg.velocity.resize(*((int*)(data + shift)));
	shift += 4;
	memcpy(msg.velocity.data(), data + shift, msg.velocity.size() * 8);
	shift += msg.velocity.size() * 8;

	// effort
	msg.effort.resize(*((int*)(data + shift)));
	shift += 4;
	memcpy(msg.effort.data(), data + shift, msg.effort.size() * 8);
	shift += msg.effort.size() * 8;

	if (shift != len) throw std::runtime_error("rosSendData(): shift != gLen");

	publisher.publish(msg);
}

void rosSpin()
{
	ros::spin();
}

void rosCallback(const sensor_msgs::JointState& msg)
{
	int len = msg.position.size() * 8 + msg.velocity.size() * 8 + msg.effort.size() * 8 + 3 * 4;
	char* data = new char[len];

	int shift = 0;

	// position
	*((int*)(data + shift)) = msg.position.size();
	shift += 4;
	memcpy(data + shift, msg.position.data(), msg.position.size() * 8);
	shift += msg.position.size() * 8;

	// velocity
	*((int*)(data + shift)) = msg.velocity.size();
	shift += 4;
	memcpy(data + shift, msg.velocity.data(), msg.velocity.size() * 8);
	shift += msg.velocity.size() * 8;

	// effort
	*((int*)(data + shift)) = msg.effort.size();
	shift += 4;
	memcpy(data + shift, msg.effort.data(), msg.effort.size() * 8);
	shift += msg.effort.size() * 8;

	if (shift != len) throw std::runtime_error("rosCallback(): shift != gLen");

	netSendData(data, len);
	delete [] data;
}

void rosInitNode(int id)
{
	int zero = 0;
	ros::init(zero, NULL, std::string("redirect_") + std::to_string(id));
	n = new ros::NodeHandle;
}

void rosDeinitNode()
{
	delete n;
}

void rosInitPublisher(Config* config)
{
	rosInitNode(config->nodeId);
	publisher = n->advertise<sensor_msgs::JointState>(config->topicName.c_str(), 1);
}

void rosDeinitPublisher()
{
	rosDeinitNode();
}

void rosInitSubscriber(Config* config)
{
	rosInitNode(config->nodeId);
	subscriber = n->subscribe(config->topicName.c_str(), 1, rosCallback);
}

void rosDeinitSubscriber()
{
	rosDeinitNode();
}
