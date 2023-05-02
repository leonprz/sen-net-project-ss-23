#pragma once
#ifndef GNSS_HPP
#define GNSS_HPP

// https://docs.rakwireless.com/Product-Categories/WisBlock/RAK12500/

#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

extern SFE_UBLOX_GNSS gnss;

void initGNSS();

#endif //GNSS_HPP
