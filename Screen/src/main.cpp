#include <Arduino.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>

#include "screen.h"
#include "touch.h"

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define MINPRESSURE 10
#define MAXPRESSURE 1000

Touch touch(XM, YM, XP, YP);
LCDWIKI_KBV lcd(ILI9486, A3, A2, A1, A0, A4);
bool isMenuPrinted = false;

void setup() {
    lcd.Init_LCD();
    lcd.Set_Rotation(3);
    Serial.begin(9600);
}

void loop() {
    if (!isMenuPrinted) {
        Draw_Menu();
    }
    TSPoint p = touch.readTouch();

    if(p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        Serial.print("X = ");
        Serial.print(map(p.y, TS_LEFT, TS_RIGHT, 0, lcd.Get_Width()));
        Serial.print("  |  Y = ");
        Serial.println(map(p.x, TS_TOP, TS_BOT, 0, lcd.Get_Height()));
    }

    delay(100);
}
