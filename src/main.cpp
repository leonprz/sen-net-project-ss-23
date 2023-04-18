/**
   @file main.cpp
   @author Marco Roobi (marco.roobi@h-brs.de)
   @brief Template
          RAK4631
   @version 1.0
   @date 2023-03-01
**/

#define EXAMPLE_TEXT "Template\n"

#include "main.h"
#include "led.hpp"
#include "serial.hpp"
#include "display.hpp"
#include "amb_light.hpp"

// variable to keep a timestamp
time_t timeout;
// actual state of one led
uint8_t led_state = HIGH;

/**
 * @brief Application specific setup functions
 *
 */
void setup()
{
  initLeds();
  initSerial();
  initDisplay();
  initAmbLight();

  digitalWrite(LED_GREEN, HIGH);

  // Add a short delay 15s before executing code
  for (uint8_t i = 0; i < 15; i++)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("\n");
  // disable the green LED
  digitalWrite(LED_GREEN, LOW);
  MYLOG("SETUP", "Starting...");

  Serial.print("============================\n");
  Serial.print("Hochschule Bonn-Rhein-Sieg\n");
  Serial.print("Smart City: Sensorik und Netze\n");
  Serial.print(EXAMPLE_TEXT);
  Serial.printf("SW Version %d.%d.%d\n", SW_VERSION_1, SW_VERSION_2, SW_VERSION_3);
  Serial.print("============================\n");

  // Keep the actual timestamp for the loop
  timeout = millis();

  display.drawStr(0, 10, "Hello World!");
  display.sendBuffer();

  // Setup finished...
  MYLOG("SETUP", "Starting LOOP...");
}

/**
 * @brief Application loop
 *
 */
void loop()
{
  // Simple non-blocking loop
  if ((millis() - timeout) > LOOP_TIMEOUT)
  {
    digitalWrite(LED_BLUE, led_state);
    digitalWrite(LED_GREEN, !led_state);
    display.clearBuffer();
    display.drawStr(0, 25, std::to_string(amb_light.readResult().lux).c_str());
    display.sendBuffer();
    led_state = !led_state;
    timeout = millis();
  }
}
