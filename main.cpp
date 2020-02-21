#include <cstdlib>
#include <string>

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
// 1. Программы завершались если версии не совпадают
// 2. Возможность закрытия клиента раньше сервера
// 3. Убрать ошибки при закрытии
// 4. Добавить возможность изменять пинг и скорость передачи данных

int main(int argc, char **argv)
{
	Config config;
	if (!config.parseArgs(argc, argv)) return 0;

	printf(" ____           ____          _ _               _   \n");
	printf("|  _ \\ ___  ___|  _ \\ ___  __| (_)_ __ ___  ___| |_ \n");
	printf("| |_) / _ \\/ __| |_) / _ \\/ _` | | '__/ _ \\/ __| __|\n");
	printf("|  _ < (_) \\__ \\  _ <  __/ (_| | | | |  __/ (__| |_ \n");
	printf("|_| \\_\\___/|___/_| \\_\\___|\\__,_|_|_|  \\___|\\___|\\__|\n");
	printf("                                        by Markovvn1\n");

	if (config.type == CONFIG_SERVER)
		netInitServer(&config);
	else
		netInitClient(&config);

	cout << config << endl;

	if (config.rosType == CONFIG_PUBLISHER)
	{
		rosInitPublisher(&config);
		netSpin();
	}
	else
	{
		rosInitSubscriber(&config);
		rosSpin();
	}

	return 0;
}
