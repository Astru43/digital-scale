#include <Arduino.h>
#include <graphic.h>

Graphics _graphics;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    Pins _pins;
    for (int i = 0; i < 8; i++) {
        if (i < 2)
            _pins.LCD_DATA[i] = i + 8;
        else
            _pins.LCD_DATA[i] = i;
    }
    _pins.LCD_RD = A0;
    _pins.LCD_WR = A1;
    _pins.LCD_RS = A2;
    _pins.LCD_CS = A3;
    _pins.LCD_RST = A4;

    _graphics = Graphics(_pins);
    uint8_t data[3] = { 0 };
    _graphics.LcdInfo(data, 3);
    Serial.println(data[0]);
    Serial.println(data[1]);
    Serial.println(data[2]);
}

void loop() {
    // put your main code here, to run repeatedly:
}