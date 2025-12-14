//const char* ssid = "Ziggo6331924";
//const char* password = "tzSxnc5y4xtr";
#include <Arduino.h>
#include <WiFiManager.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 6, /* data=*/ 5);

#define BLUE_LED 8
#define BOOT_BUTTON 9

WiFiManager wm;

void setup() {
  Serial.begin(115200);
  
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BOOT_BUTTON, INPUT_PULLUP);
  digitalWrite(BLUE_LED, HIGH);
  
  u8g2.begin();
  u8g2.setContrast(30);
  u8g2.setFont(u8g2_font_7x13_tr);
  
  // Show connecting message
  u8g2.clearBuffer();
  u8g2.drawStr(2, 12, "Connecting");
  u8g2.drawStr(2, 25, "to WiFi...");
  u8g2.sendBuffer();
  
  // Blink while connecting
  digitalWrite(BLUE_LED, LOW);
  delay(200);
  digitalWrite(BLUE_LED, HIGH);
  delay(200);
  digitalWrite(BLUE_LED, LOW);
  
  // Auto-connect: uses saved credentials or starts portal if none exist
  wm.setConfigPortalTimeout(180); // 3 min timeout for config portal
  bool connected = wm.autoConnect("ESP32-Setup");
  
  if (connected) {
    digitalWrite(BLUE_LED, LOW);  // LED on
    
    u8g2.clearBuffer();
    u8g2.drawStr(2, 12, "Connected");
    u8g2.drawStr(2, 25, "to WiFi");
    u8g2.sendBuffer();
    
    Serial.println("\nConnected to WiFi");
    Serial.println(WiFi.localIP());
  } else {
    u8g2.clearBuffer();
    u8g2.drawStr(2, 12, "Config");
    u8g2.drawStr(2, 25, "timeout");
    u8g2.sendBuffer();
  }
}

void loop() {
  // Keep LED on when connected
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(BLUE_LED, LOW);
  } else {
    // Blink when disconnected
    digitalWrite(BLUE_LED, !digitalRead(BLUE_LED));
    delay(500);
  }
  
  // Check if BOOT button held for 3 seconds - reset WiFi
  if (digitalRead(BOOT_BUTTON) == LOW) {
    unsigned long pressStart = millis();
    
    u8g2.clearBuffer();
    u8g2.drawStr(2, 12, "Hold for");
    u8g2.drawStr(2, 25, "reset...");
    u8g2.sendBuffer();
    
    while (digitalRead(BOOT_BUTTON) == LOW) {
      if (millis() - pressStart > 3000) {
        // Button held for 3 seconds
        u8g2.clearBuffer();
        u8g2.drawStr(2, 12, "Resetting");
        u8g2.drawStr(2, 25, "WiFi...");
        u8g2.sendBuffer();
        
        wm.resetSettings();
        delay(1000);
        ESP.restart();
      }
      delay(100);
    }
    
    // Button released before 3 seconds
    u8g2.clearBuffer();
    u8g2.drawStr(2, 12, "Cancelled");
    u8g2.sendBuffer();
    delay(1000);
  }
}