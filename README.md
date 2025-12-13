# ESP32-C3 OLED Hello World

A simple "Hello World" example for ESP32-C3 development boards with integrated 0.42" OLED display.

## Hardware

- **Board:** ESP32-C3 OLED Development Board
- **Display:** 0.42" OLED (SSD1306 driver)

## Display Specifications

- **Resolution:** 64x48 pixels
- **Driver:** SSD1306
- **I2C Address:** 0x3C
- **I2C Pins:**
  - SDA: GPIO5
  - SCL: GPIO6

## Software Requirements

- Visual Studio Code
- PlatformIO Extension

## Installation

1. Clone or download this repository
2. Open the project folder in VS Code with PlatformIO
3. Connect your ESP32-C3 board via USB-C
4. Click the arrow (→) icon at the bottom to upload

## Usage

After uploading, the OLED display will show:
```
Hello
World!
```

## License

MIT License - feel free to use this code for your projects!