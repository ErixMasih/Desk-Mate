ESP32 Dev Board + SSD1306 OLED Display Module + TTP223 Capacitive Touch Sensor Module Connection Table
| OLED Pin | ESP32 Pin |
| -------- | --------- |
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO 21   |
| SCL      | GPIO 22   |


| TTP223 Pin | ESP32 Pin |
| ---------- | --------- |
| VCC        | 3.3V      |
| GND        | GND       |
| OUT        | GPIO 4    |


OLED SDA  -> GPIO 21
OLED SCL  -> GPIO 22

TTP223 OUT -> GPIO 4

All GNDs connected together
All VCCs connected to 3.3V

Important
Use 3.3V, NOT 5V
Make sure OLED address is 0x3C
If screen stays black, try 0x3D

Your setup is basically:

ESP32
 ├── OLED Display
 └── TTP223 Touch Button
