/*
 *  Project: ros_redirect
 *  File: config.hpp
 *
 *  Date: 20.02.2020
 *  Author: Markovvn1
 */

#pragma once

#include <iostream>
#include <string>

#define CONFIG_CLIENT 0
#define CONFIG_SERVER 1

#define CONFIG_SUBSCRIBER 0
#define CONFIG_PUBLISHER 1

class Config
{
private:
	void showLog();
	void showShortHelp(const char* prog);
	void showHelp(const char* prog);
	void showUnrecOp(const char* prog, const char* op);

public:
	int type; // CONFIG_CLIENT, CONFIG_SERVER
	std::string address;
	int rosType; // CONFIG_SUBSCRIBER, CONFIG_PUBLISHER
	std::string topicName; // name of topic
	int nodeId;

	Config();
	bool parseArgs(int argc, char** argv);

	friend std::ostream& operator <<(std::ostream& out, const Config& config);
};


