#include "env_sensor.hpp"
#include "debug.hpp"

Adafruit_BME680 env_sensor;

void initEnvSensor()
{
	if (!env_sensor.begin(BME680_ADDRESS))
	{
		MYLOG("ENV_SENSOR", "Could not find a valid BME680 sensor, check wiring!");
		return;
	}

	env_sensor.setTemperatureOversampling(BME680_OS_8X);
	env_sensor.setHumidityOversampling(BME680_OS_2X);
	env_sensor.setPressureOversampling(BME680_OS_4X);
	env_sensor.setIIRFilterSize(BME680_FILTER_SIZE_3);
	env_sensor.setGasHeater(0, 0); // disables gas heater
}
