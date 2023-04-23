/**
   @file main.h
   @author Marco Roobi (marco.roobi@h-brs.de)
   @brief Header File
          RAK4631
   @version 1.0
   @date 2023-03-01
 **/

#ifndef MAIN_H
#define MAIN_H

//***********************************************/
//** Set the application firmware version here  */
//** (in PlatformIO this is done automatically) */
//***********************************************/
// ; major version increase on API change / not backwards compatible
#ifndef SW_VERSION_1
  #define SW_VERSION_1 1
#endif
// ; minor version increase on API change / backward compatible
#ifndef SW_VERSION_2
  #define SW_VERSION_2 0
#endif
// ; patch version increase on bugfix, no affect on API
#ifndef SW_VERSION_3
  #define SW_VERSION_3 0
#endif

/** Include library's */
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
/** Include TwoWire and SPI Interface */
#include <SPI.h>
#include <Wire.h>
/** Include the SX126x-API */
#include <SX126x-Arduino.h>
/** Add your required includes after SX126x-Arduino.h */
#include <string>

#include "debug.hpp"

// ADD YOUR CODE HERE
#define LOOP_TIMEOUT 1000
#define SOIL_PIN WB_A1
#define PIR_PIN WB_IO1

#endif  // MAIN_H
