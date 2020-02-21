/*
 *  Project: ros_redirect
 *  File: config.cpp
 *
 *  Date: 20.02.2020
 *  Author: Markovvn1
 */

#include "config.hpp"

#include <map>
#include <cstdio>
#include <string>

using std::map;
using std::string;

Config::Config()
{
	type = -1;
	rosType = 0;
}

void Config::showLog()
{
	printf("RosRedirect version 1.0 (by Markovvn1)\n");
}

void Config::showShortHelp(const char* prog)
{
	showLog();
	printf("Usage: %s OPTIONS [SERVER_OPTIONS]\n", prog);
}

void Config::showHelp(const char* prog)
{
	showShortHelp(prog);
	printf("\n");
	printf("Getting help:\n");
	printf("    --help               show this message\n");
	printf("    -h                   show this message\n");
	printf("\n");
	printf("Global options:\n");
	printf("    --server PORT        run as server and use port PORT\n");
	printf("    --client IP:PORT     run as client and connect to server on IP:PORT\n");
	printf("\n");
	printf("Server options:\n");
	printf("    --subscribe TOPIC    subscribe to topic TOPIC\n");
	printf("    --publish TOPIC      publish to topic TOPIC\n");
	printf("\n");
}

void Config::showUnrecOp(const char* prog, const char* op)
{
	showLog();
	printf("Unrecognized option \"%s\".\n", op);
	printf("Call %s --help to get help\n", prog);
}

bool Config::parseArgs(int argc, char** argv)
{
	string s;
	if (argc < 2)
	{
		showShortHelp(argv[0]);
		return false;
	}

	s = string(argv[1]);
	if (s == "--help" || s == "-h")
	{
		showHelp(argv[0]);
		return false;
	}
	else if (argc < 3)
	{
		showUnrecOp(argv[0], s.c_str());
		return false;
	}

	if (s == "--client")
	{
		type = CONFIG_CLIENT;
		address = string(argv[2]);
	}
	else if (s == "--server")
	{
		type = CONFIG_SERVER;
		address = string(argv[2]);
	}
	else
	{
		showUnrecOp(argv[0], s.c_str());
		return false;
	}

	if (type == 1)
	{
		if (argc != 5)
		{
			showShortHelp(argv[0]);
			return false;
		}

		s = string(argv[3]);
		if (s == "--subscribe")
		{
			rosType = CONFIG_SUBSCRIBER;
		}
		else if (s == "--publish")
		{
			rosType = CONFIG_PUBLISHER;
		}
		else
		{
			showUnrecOp(argv[0], s.c_str());
			return false;
		}

		topicName = string(argv[4]);
	}

	return true;
}

std::ostream& operator <<(std::ostream& out, const Config& config)
{
	out << "type:      " << (config.type == CONFIG_CLIENT ? "client" : "server") << std::endl;
	if (config.type == CONFIG_CLIENT)
	out << "address:   " << config.address << std::endl;
	if (config.type == CONFIG_SERVER)
	out << "port:      " << config.address << std::endl;
	out << "rosType:   " << (config.rosType == CONFIG_SUBSCRIBER ? "subscriber" : "publisher");
	out << std::endl;
	out << "topicName: " << config.topicName;

	return out;
}
