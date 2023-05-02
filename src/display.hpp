#pragma once
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

// https://docs.rakwireless.com/Product-Categories/WisBlock/RAK1921/

#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C display;

void initDisplay();

#endif // DISPLAY_HPP
