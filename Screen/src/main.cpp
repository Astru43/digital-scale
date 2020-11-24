#include <Arduino.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>

LCDWIKI_KBV lcd(ILI9486, A3, A2, A1, A0, A4);

void setup() {
    // put your setup code here, to run once:
    lcd.Init_LCD();
    lcd.Set_Rotation(3);
    lcd.Fill_Screen(17, 17, 17);
    lcd.Set_Draw_color(235, 32, 250);
    lcd.Draw_Rectangle(0, 0, lcd.Get_Width() - 1, lcd.Get_Height() / 2 - 2);

    lcd.Set_Text_Size(2);
    lcd.Set_Text_Mode(1);
    lcd.Print_String("Hello World", CENTER, lcd.Get_Height() / 4 - 1);
    lcd.Set_Text_Mode(0);

    lcd.Set_Draw_color(35, 190, 235);
    lcd.Fill_Rectangle(0, lcd.Get_Height() / 2 + 1, lcd.Get_Width() - 1, lcd.Get_Height() - 1);
}

void loop() {
    // put your main code here, to run repeatedly:
    delay(3000);
}