#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
  delay(1000);

  Wire.begin(5, 6);
  delay(100);

  if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    display.clearDisplay();
    display.display();
    delay(100);

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.print("Lights");

    display.setCursor(0, 12);
    display.print("On:  18:30");

    display.setCursor(0, 24);
    display.print("Off: 23:00");

    display.display();
  }
}

void loop()
{
}