//const char* ssid = "Ziggo6331924";
//const char* password = "tzSxnc5y4xtr";
#include <Arduino.h>
#include <WiFi.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 6, /* data=*/ 5);

const char* ssid = "Ziggo6331924";
const char* password = "tzSxnc5y4xtr";

#define BLUE_LED 8  // Blue LED on GPIO8

void setup() {
  Serial.begin(115200);
  
  // Setup blue LED
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(BLUE_LED, HIGH);  // Try starting HIGH
  
  u8g2.begin();
  u8g2.setContrast(30);
  u8g2.setFont(u8g2_font_7x13_tr);
  
  // Connect to WiFi
  u8g2.clearBuffer();
  u8g2.drawStr(2, 12, "Connecting");
  u8g2.drawStr(2, 25, "to WiFi...");
  u8g2.sendBuffer();
  
  WiFi.begin(ssid, password);
  
  // Blink blue LED while connecting
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(BLUE_LED, LOW);   // Swap HIGH/LOW
    delay(250);
    digitalWrite(BLUE_LED, HIGH);
    delay(250);
    Serial.print(".");
  }
  
  // Turn LED ON when connected (LOW = on for active-low LED)
  digitalWrite(BLUE_LED, LOW);
  
  // Connected!
  u8g2.clearBuffer();
  u8g2.drawStr(2, 12, "Connected");
  u8g2.drawStr(2, 25, "to WiFi");
  u8g2.sendBuffer();
  
  Serial.println("\nConnected to WiFi");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Keep LED on when connected
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(BLUE_LED, LOW);  // LOW = on
  } else {
    digitalWrite(BLUE_LED, !digitalRead(BLUE_LED));
    delay(500);
  }
}