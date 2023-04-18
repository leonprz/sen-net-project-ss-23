#pragma once
#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <Arduino.h>

#define BAUD_RATE 115200
#define SERIAL_MAX_WAIT 5000 // ms

void initSerial();

#endif // SERIAL_HPP
