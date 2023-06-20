/**
	 @file main.cpp
	 @author Marco Roobi (marco.roobi@h-brs.de)
	 @brief Template
					RAK4631
	 @version 1.0
	 @date 2023-03-01
**/

#define DISPLAY_PAGES 2

#include "main.h"
#include "led.hpp"
#include "serial.hpp"
#include "display.hpp"
#include "lorawan/lorawan.hpp"
#include "lorawan/encoding.hpp"
#include "sensors/amb_light.hpp"
#include "sensors/env_sensor.hpp"

// variable to keep a timestamp
time_t timeout_display;
time_t timeout_lora;

// actual state of one led
uint8_t led_state = HIGH;
uint8_t display_paging = 0;

/**
 * @brief Application specific setup functions
 *
 */
void setup()
{
	// Initialize the LEDs
	initLeds();

	digitalWrite(LED_BLUE, HIGH);

	// Add a short delay 15s before executing code
	for (uint8_t i = 0; i < 15; i++)
	{
		delay(1000);

		Serial.print(".");

		digitalWrite(LED_GREEN, led_state);
		led_state = !led_state;
	}
	Serial.print("\n");

	initSerial();
	initDisplay();
	initLoRaWan();
	initAmbLight();
	initEnvSensor();

	digitalWrite(LED_BLUE, LOW);
	digitalWrite(LED_GREEN, HIGH);

	MYLOG("SETUP", "Starting...");

	Serial.print("============================\n");
	Serial.print("Hochschule Bonn-Rhein-Sieg\n");
	Serial.print("Smart City: Sensorik und Netze\n");
	Serial.print("Air Quality Monitoring\n");
	Serial.printf("SW Version %d.%d.%d\n", SW_VERSION_1, SW_VERSION_2, SW_VERSION_3);
	Serial.print("============================\n");

	display.drawStr(0, 30, "Air Quality");
	display.drawStr(0, 45, "Monitoring");
	display.sendBuffer();

	digitalWrite(LED_GREEN, LOW);

	// Keep the actual timestamp for the loop
	timeout_display = millis();
	timeout_lora = millis();

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
	if ((millis() - timeout_display) > DISPLAY_LOOP_TIMEOUT)
	{
		digitalWrite(LED_BLUE, led_state);
		digitalWrite(LED_GREEN, !led_state);

		// Read the environment sensor
		if (!env_sensor.performReading())
		{
			MYLOG("ENV_SENSOR", "Failed to perform reading!");
		}

		display.clearBuffer();
		if (display_paging == 0)
		{
			display.drawStr(0, 15, (std::to_string(amb_light.readResult().lux) + " Lux").c_str());
			display.drawStr(0, 30, (std::to_string(env_sensor.temperature) + " *C").c_str());
			display.drawStr(0, 45, (std::to_string(env_sensor.humidity) + " %").c_str());
			display.drawStr(0, 60, (std::to_string(env_sensor.pressure / 100.0) + " hPa").c_str());
		}
		else if (display_paging == 1)
		{
			display.drawStr(0, 15, ("LoRa " + (std::string)(lora_isJoined ? "connected" : "failed")).c_str());
			display.drawStr(0, 30, ("SF" + std::to_string(SX126x.ModulationParams.Params.LoRa.SpreadingFactor)).c_str());
			display.drawStr(0, 45, ("Sent: " + std::to_string(lora_getMsgCount())).c_str());

			uint32_t next_send = (uint32_t)(timeout_lora + LORA_LOOP_TIMEOUT - millis()) / 1000;
			uint32_t next_send_min = next_send / 60;
			std::string next_msg = "Next: ";
			if (next_send_min > 0)
			{
				next_msg += std::to_string(next_send_min) + "min ";
			}
			next_msg += std::to_string(next_send % 60) + "s";
			
			display.drawStr(0, 60, next_msg.c_str());
		}
		display.sendBuffer();

		led_state = !led_state;
		display_paging = ++display_paging % DISPLAY_PAGES;
		timeout_display = millis();
	}

	if ((millis() - timeout_lora) > LORA_LOOP_TIMEOUT)
	{
		if (lora_isJoined)
		{
			lora_send_data();
		}

		timeout_lora = millis();
	}
}
