#include "amb_light.hpp"
#include "debug.hpp"

ClosedCube_OPT3001 amb_light;

void initAmbLight()
{
	amb_light.begin(OPT3001_ADDRESS);

	OPT3001_Config newConfig;
	newConfig.RangeNumber = B1100;
	newConfig.ConvertionTime = B0;
	newConfig.Latch = B1;
	newConfig.ModeOfConversionOperation = B11;

	OPT3001_ErrorCode error = amb_light.writeConfig(newConfig);
	if (error != NO_ERROR)
	{
		MYLOG("AMB_LIGHT", "Could not write config! [Error: %d]", error);
		return;
	}
}
