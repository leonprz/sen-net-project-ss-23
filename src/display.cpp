#include "display.hpp"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0);

void initDisplay()
{
	display.begin();
	display.setFont(u8g2_font_ncenB10_tr);
	display.clearBuffer();
}
