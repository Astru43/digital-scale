#include <Arduino.h>
//Library for controlling the lcd
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>

#include "screen.h"
#include "touch.h"

//Arduino pins for reading touch input
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

Touch touch(XM, YM, XP, YP);                   //Touch class that handels checking hitboxies
LCDWIKI_KBV lcd(ILI9486, A3, A2, A1, A0, A4);  //Library implementation of lcd control
bool isMenuPrinted = false;                    //A global varible for keeping track of menu printing

void setup() {
    lcd.Init_LCD();       //Initialize the lcd and the library
    lcd.Set_Rotation(3);  //Set lcd to horizontal
    Serial.begin(9600);   //Debuging serial

    Serial1.begin(2000000);  //Initialize serial with the other arduino
    InitScreen();            //Initialize the screen animations
}

void loop() {
    if (!isMenuPrinted) {
        //Draw the main menu
        Draw_Menu(&touch);
    }
    touch.hitboxClicked(lcd);  //Check hitbox hits
    playAnimations();          //Play animations
    delay(100);                //Wait 100ms
}
