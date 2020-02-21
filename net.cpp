/*
 *  Project: ros_redirect
 *  File: net.cpp
 *
 *  Date: 21.02.2020
 *  Author: Markovvn1
 */

#include "net.hpp"
#include "ros.hpp"

#include "CrossSocket/socket.hpp"
#include "compile_time.hpp"

#define VERSION __TIME_UNIX__

#include <unistd.h>

ServerSocket server;
Socket client;

void netSendData(const char* data, int len)
{
	client.send((char*)&len, 4);
	client.send(data, len);
}

void netSpin()
{
	while (client.isActive())
	{
		int len;
		client.recv((char*)&len, 4);

		char* buf = new char[len];
		client.recv(buf, len);
		rosSendData(buf, len);
		delete [] buf;
	}
}

void netInitServer(Config* config)
{
	server.open();
	server.bind(stoi(config->address));
	server.listen(5);

	if (!server.isActive()) return;

	while (true)
	{
		client = server.accept();

		if (!client.isActive())
		{
			usleep(10000);
			continue;
		}

		break;
	}

	// version verification
	uint64_t version = VERSION;
	client.send((char*)&version, 8);

	int clientRosType = config->rosType == CONFIG_SUBSCRIBER ? CONFIG_PUBLISHER : CONFIG_SUBSCRIBER;
	client.send((char*)&clientRosType, 4);
	int len = config->topicName.length();
	client.send((char*)&len, 4);
	client.send(config->topicName.c_str(), len);
}

void netDeinitServer()
{
	client.close();
	server.close();
}

void netInitClient(Config* config)
{
	client.open();
	int i = config->address.find(':');
	if (i < 0) return;
	config->address[i] = 0;
	while (!client.isActive())
		client.connect(config->address.c_str(), atoi(config->address.c_str() + i + 1));
	config->address[i] = ':';

	// version verification
	uint64_t version;
	client.recv((char*)&version, 8);
	if (version != VERSION)
	{
		client.close();
		printf("You use different version of software!\n");
		return;
	}

	client.recv((char*)&config->rosType, 4);
	int len;
	client.recv((char*)&len, 4);
	config->topicName.resize(len);
	client.recv(&config->topicName[0], len);
}

void netDeinitClient()
{
	client.close();
}
