#include <cstdlib>
#include <string>
#include <csignal>

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
typedef sensor_msgs::JointState RedirectType;

#include "config.hpp"
#include "ros.hpp"
#include "net.hpp"

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::to_string;

// TODO:
// 1. При закрытии клиента сервер тоже закрывался
// 2. Добавить возможность измерять пинг и скорость передачи данных

typedef bool (*Func)(Config* config);

Config* pconfig;
Func netDeinit = NULL, rosDeinit = NULL;

void onClose(int s = 0)
{
	if (netDeinit) netDeinit(pconfig);
	netDeinit = NULL;
	if (rosDeinit) rosDeinit(pconfig);
	rosDeinit = NULL;
}

int main(int argc, char **argv)
{
	Config config;
	pconfig = &config;
	if (!config.parseArgs(argc, argv)) return 0;

	printf(" ____           ____          _ _               _   \n");
	printf("|  _ \\ ___  ___|  _ \\ ___  __| (_)_ __ ___  ___| |_ \n");
	printf("| |_) / _ \\/ __| |_) / _ \\/ _` | | '__/ _ \\/ __| __|\n");
	printf("|  _ < (_) \\__ \\  _ <  __/ (_| | | | |  __/ (__| |_ \n");
	printf("|_| \\_\\___/|___/_| \\_\\___|\\__,_|_|_|  \\___|\\___|\\__|\n");
	printf("                                        by Markovvn1\n");

	Func netInit = config.type == CONFIG_SERVER ? netInitServer : netInitClient;
	netDeinit = config.type == CONFIG_SERVER ? netDeinitServer : netDeinitClient;

	if (!netInit(pconfig))
	{
		netDeinit(pconfig);
		return 1;
	}

	Func rosInit = config.rosType == CONFIG_PUBLISHER ? rosInitPublisher : rosInitSubscriber;
	rosDeinit = config.rosType == CONFIG_PUBLISHER ? rosDeinitPublisher : rosDeinitSubscriber;
	Func spin = config.rosType == CONFIG_PUBLISHER ? netSpin : rosSpin;

	cout << endl << config << endl << endl;

	rosInit(pconfig);

	if (config.rosType == CONFIG_PUBLISHER)
	{
		// Перехват завершения программы
		struct sigaction sigIntHandler;
		sigIntHandler.sa_handler = onClose;
		sigemptyset(&sigIntHandler.sa_mask);
		sigIntHandler.sa_flags = 0;
		sigaction(SIGINT, &sigIntHandler, NULL);
	}

	printf("[LOG]: Connection established\n");

	spin(pconfig);

	onClose();

	return 0;
}
