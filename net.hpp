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
void netSpin(); // В этой функции происходит вызов rosSendData

void netInitServer(Config* config);
void netDeinitServer();
void netInitClient(Config* config);
void netDeinitClient();
