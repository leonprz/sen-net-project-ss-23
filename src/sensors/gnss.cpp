#include "gnss.hpp"
#include "debug.hpp"

SFE_UBLOX_GNSS gnss;

void initGNSS()
{
	pinMode(WB_IO2, OUTPUT);
	digitalWrite(WB_IO2, 0);
	delay(1000);
	digitalWrite(WB_IO2, 1);
	delay(1000);

	if (!gnss.begin())
	{
		MYLOG("GNSS", "Could not find a valid GNSS sensor, check wiring!");
		return;
	}

	gnss.setI2COutput(COM_TYPE_UBX);				 // Set the I2C port to output UBX only (turn off NMEA noise)
	gnss.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); // Save (only) the communications port settings to flash and BBR
}
