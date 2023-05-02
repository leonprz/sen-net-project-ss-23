#pragma once
#ifndef ENV_SENSOR_HPP
#define ENV_SENSOR_HPP

// https://docs.rakwireless.com/Product-Categories/WisBlock/RAK1906/

#include <Adafruit_BME680.h>

#define BME680_ADDRESS 0x76

extern Adafruit_BME680 env_sensor;

void initEnvSensor();

#endif // ENV_SENSOR_HPP
