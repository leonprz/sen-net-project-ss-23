#include "serial.hpp"

void initSerial()
{
	// Initialize Serial for debug output
	Serial.begin(BAUD_RATE);

	// Initialize Serial for debug output
	uint32_t start = millis();
	Serial.begin(BAUD_RATE);
	while (!Serial)
	{
		if ((millis() - start) < SERIAL_MAX_WAIT)
		{
			delay(100);
		}
		else
		{
			break;
		}
	}

	// We should now have a serial interface...
}
