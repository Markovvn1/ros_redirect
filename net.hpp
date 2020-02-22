/*
 *  Project: ros_redirect
 *  File: net.hpp
 *
 *  Date: 21.02.2020
 *  Author: Markovvn1
 */

#pragma once

#include <stdlib.h>
#include <string>

#include "config.hpp"

// Функцию вызывает ros когда хочет отправить сообщение в net
// Вызывается только если был вызыван rosInitSubscriber (именно ros)
void netSendData(const char* data, int len);

// Вызывается только если был вызыван rosInitPubliser (именно ros)
bool netSpin(Config* config); // В этой функции происходит вызов rosSendData

bool netInitServer(Config* config);
bool netDeinitServer(Config* config);
bool netInitClient(Config* config);
bool netDeinitClient(Config* config);
