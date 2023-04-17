/**
   @file main.cpp
   @author Marco Roobi (marco.roobi@h-brs.de)
   @brief Template
          RAK4631
   @version 1.0
   @date 2023-03-01
**/

#define EXAMPLE_TEXT "Template\n"

#include "main.h"

// variable to keep a timestamp
time_t timeout;
// actual state of one led
uint8_t led_state = HIGH;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

// forward declarations (needed for platformIO)
void initLeds();
void initSerial();
void initDisplay();

/**
 * @brief Application specific setup functions
 *
 */
void setup(void)
{
  initLeds();
  initSerial();
  initDisplay();

  // ADD YOUR CODE HERE

  // Keep the actual timestamp for the loop
  timeout = millis();

  u8g2.drawStr(0, 20, "Hello World!");
  u8g2.sendBuffer();

  // Setup finished...
  MYLOG("SETUP", "Starting LOOP...");
}

/**
 * @brief Application loop
 *
 */
void loop(void)
{
  // Simple non-blocking loop
  if ((millis() - timeout) > LOOP_TIMEOUT)
  {
    digitalWrite(LED_BLUE,  led_state);
    digitalWrite(LED_GREEN,!led_state);
    led_state = !led_state;
    timeout = millis();
  }
}

void initLeds()
{
  // Set GPIOs for LED's as Output
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  // Set the GPIOs LOW (disable LEDs)
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
}

void initSerial()
{
  // Initialize Serial for debug output
  digitalWrite(LED_GREEN, HIGH);
  Serial.begin(115200);

  // Initialize Serial for debug output
  timeout = millis();
  Serial.begin(115200);
  while (!Serial)
  {
    if ((millis() - timeout) < 5000)
    {
      delay(100);
    }
    else
    {
      break;
    }
  }
  // We should now have a serial interface...
  // Add a short delay 15s before executing code
  for(uint8_t i=0; i < 15;i++){
    delay(1000);
    Serial.print(".");
  }
  Serial.print("\n");
  // disable the green LED
  digitalWrite(LED_GREEN, LOW);
  MYLOG("SETUP", "Starting...");

  Serial.print("============================\n");
  Serial.print("Hochschule Bonn-Rhein-Sieg\n");
  Serial.print("Smart City: Sensorik und Netze\n");
  Serial.print(EXAMPLE_TEXT);
  Serial.printf("SW Version %d.%d.%d\n", SW_VERSION_1, SW_VERSION_2, SW_VERSION_3);
  Serial.print("============================\n");
}

void initDisplay() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.clearBuffer();
}
