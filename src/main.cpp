#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 6, /* data=*/ 5);

void setup() {
  u8g2.begin();
  
  // Adjust contrast - try values between 0-255
  // Start with 128 (medium) and adjust to taste
  u8g2.setContrast(30);  // Try 100, 80, 60 if still too bright
  
  u8g2.clearBuffer();
  
  // Try a non-bold font
  // u8g2_font_6x10_tr - clean, regular
  // u8g2_font_5x7_tr - smaller, lighter
  u8g2.setFont(u8g2_font_7x13_tr);  // Regular weight font
  
  u8g2.drawStr(2, 8, "Lights");
  u8g2.drawStr(2, 25, "On:  18:30");
  u8g2.drawStr(2, 38, "Off: 22:45");
  
  u8g2.sendBuffer();
}

void loop() {
}