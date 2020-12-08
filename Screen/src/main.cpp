#include <Arduino.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>

#include "screen.h"
#include "touch.h"

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

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
        Draw_Menu(&touch);
    }
    TSPoint p = touch.readTouch(lcd);
    touch.hitboxClicked(lcd);

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        Serial.print("X = ");
        Serial.print(p.x);
        Serial.print("  |  Y = ");
        Serial.println(p.y);
    }

    delay(100);
}
