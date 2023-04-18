#pragma once
#ifndef AMB_LIGHT_HPP
#define AMB_LIGHT_HPP

#include <ClosedCube_OPT3001.h>

#define OPT3001_ADDRESS 0x44

extern ClosedCube_OPT3001 amb_light;

void initAmbLight();

#endif // AMB_LIGHT_HPP