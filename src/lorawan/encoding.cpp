#include "encoding.hpp"
#include "sensors/amb_light.hpp"
#include "sensors/env_sensor.hpp"
#include "debug.hpp"

uint24 encode_ambLight()
{
	float lux = amb_light.readResult().lux;

	// to be changed

	return (uint24)lux;
}

uint32_t encode_envSensor()
{
	float temperature = env_sensor.temperature;
	float humidity = env_sensor.humidity;
	uint32_t pressure = env_sensor.pressure;

	uint32_t data = 0;
	// 0-7: temperature
	data |= (uint32_t)temperature << 1;
	data |= temperature - (uint32_t)temperature < 0.5 ? 0 : 1;
	// 8-15: humidity
	data |= (uint32_t)humidity << 9;
	data |= (humidity - (uint32_t)humidity < 0.5 ? 0 : 1) << 8;
	// 16-31: pressure
	data |= pressure << 17;

	return data;
}
