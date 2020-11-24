#include <Arduino.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>

LCDWIKI_KBV lcd(ILI9486, A3, A2, A1, A0, A4);
bool isMenuPrinted = false;

void Draw_Menu();

void setup() {
    // put your setup code here, to run once:
    lcd.Init_LCD();
    lcd.Set_Rotation(3);
}

void loop() {
    // put your main code here, to run repeatedly:
    if (!isMenuPrinted) Draw_Menu();
    delay(3000);
}

void Draw_Menu() {
    lcd.Fill_Screen(17, 17, 17);
    lcd.Set_Draw_color(235, 32, 250);
    lcd.Draw_Rectangle(0, 0, lcd.Get_Width() - 1, lcd.Get_Height() / 2 - 2);

    lcd.Set_Text_Size(2);
    lcd.Set_Text_Mode(1);
    lcd.Print_String("Hello World", CENTER, lcd.Get_Height() / 4 - 1);
    lcd.Set_Text_Mode(0);

    lcd.Set_Draw_color(35, 190, 235);
    lcd.Fill_Rectangle(0, lcd.Get_Height() / 2 + 1, lcd.Get_Width() - 1, lcd.Get_Height() - 1);

    lcd.Set_Draw_color(34,139,34);
    lcd.Fill_Round_Rectangle(10, lcd.Get_Height() / 2 + 1 + 10, lcd.Get_Width() / 3 - 1 - 5, lcd.Get_Height() - 1 - 10, 20);

    lcd.Set_Draw_color(25, 25, 112);
    lcd.Fill_Round_Rectangle(lcd.Get_Width() / 3 -1 + 5, lcd.Get_Height() / 2 + 1 + 10, lcd.Get_Width() / 3 * 2 - 1 - 5, lcd.Get_Height() - 1 - 10, 20);

    lcd.Set_Draw_color(199,21,133);
    lcd.Fill_Round_Rectangle(lcd.Get_Width() / 3 * 2 + 5, lcd.Get_Height() / 2 + 1 + 10, lcd.Get_Width() - 1 - 10, lcd.Get_Height() - 1 - 10, 20);

    isMenuPrinted = true;
}