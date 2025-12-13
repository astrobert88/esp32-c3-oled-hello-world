#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 48

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
  Wire.begin(5, 6);
  delay(100);

  if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    // Clear multiple times to ensure all pixels are off
    display.clearDisplay();
    display.display();
    delay(100);

    display.clearDisplay();
    display.display();
    delay(100);

    // Now draw the text
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Hello");
    display.println("World!");
    display.display();
  }
  else
  {
    pinMode(2, OUTPUT);
    while (1)
    {
      digitalWrite(2, !digitalRead(2));
      delay(300);
    }
  }
}

void loop()
{
}