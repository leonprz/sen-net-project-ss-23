#pragma once
#ifndef SOIL_SENSOR_HPP
#define SOIL_SENSOR_HPP

// https://www.az-delivery.de/en/products/bodenfeuchte-sensor-modul-v1-2?variant=12461193855072

#include <Arduino.h>

#define SOIL_PIN WB_A1

void initSoilSensor();

#endif //SOIL_SENSOR_HPP
