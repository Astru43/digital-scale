#include <Arduino.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>

#include "screen.h"

LCDWIKI_KBV lcd(ILI9486, A3, A2, A1, A0, A4);
bool isMenuPrinted = false;

void setup() {
    lcd.Init_LCD();
    lcd.Set_Rotation(3);
}

void loop() {
    if (!isMenuPrinted) {
        Draw_Menu();
    }
    delay(3000);
}
