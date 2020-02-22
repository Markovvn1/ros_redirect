/*
 *  Project: ros_redirect
 *  File: ros.hpp
 *
 *  Date: 21.02.2020
 *  Author: Markovvn1
 */

#pragma once

#include "config.hpp"

// Функцию вызывает net когда хочет отправить сообщение в ros
// Вызывается только если был вызыван rosInitPublisher
void rosSendData(const char* data, int len);

// Вызывается только если был вызыван rosInitSubscriber
bool rosSpin(Config* config); // В этой функции происходит вызов netSendData

bool rosInitPublisher(Config* config);
bool rosDeinitPublisher(Config* config);
bool rosInitSubscriber(Config* config);
bool rosDeinitSubscriber(Config* config);
