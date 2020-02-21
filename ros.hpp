/*
 *  Project: ros_redirect
 *  File: ros.hpp
 *
 *  Date: 21.02.2020
 *  Author: Markovvn1
 */

#pragma once

// Функцию вызывает net когда хочет отправить сообщение в ros
// Вызывается только если был вызыван rosInitPublisher
void rosSendData(const char* data, int len);

// Вызывается только если был вызыван rosInitSubscriber
void rosSpin(); // В этой функции происходит вызов netSendData

void rosInitPublisher(const char* name);
void rosDeinitPublisher();
void rosInitSubscriber(const char* name);
void rosDeinitSubscriber();
