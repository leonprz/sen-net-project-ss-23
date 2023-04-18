#include "led.hpp"

void initLeds()
{
	// Set GPIOs for LED's as Output
	pinMode(LED_GREEN, OUTPUT);
	pinMode(LED_BLUE, OUTPUT);

	// Set the GPIOs LOW (disable LEDs)
	digitalWrite(LED_GREEN, LOW);
	digitalWrite(LED_BLUE, LOW);
}
