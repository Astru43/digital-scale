#include "screen.h"

struct animation_t {
    uint16_t x1;
    uint16_t y1;
    uint16_t x2;
    uint16_t y2;

    uint8_t state = 0;
    bool playAnimation = false;

    animation_t() {}
    animation_t(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2) {
        x1 = X1;
        x2 = X2;
        y1 = Y1;
        y2 = Y2;
    }
};

animation_t animation1;
animation_t animation2;


void clickAnimation1() {
    switch (animation1.state) {
        case 0:
            lcd.Set_Draw_color(40, 40, 40);
            lcd.Fill_Round_Rectangle(animation1.x1, animation1.y1, animation1.x2, animation1.y2, 20);
            animation1.state = 1;
            break;
        case 1:
            lcd.Set_Draw_color(34, 139, 34);
            lcd.Fill_Round_Rectangle(animation1.x1, animation1.y1, animation1.x2, animation1.y2, 20);
            animation1.playAnimation = false;
            animation1.state = 0;
            break;
    }

    lcd.Set_Text_Size(2);
    lcd.Set_Text_Mode(1);
    uint32_t len = Pixel_srtlen("Tare", 2);
    uint32_t x = String_x_pos(6, len);
    uint32_t y = String_y_pos(4, 3, 2);
    lcd.Print_String("Tare", x, y);
    lcd.Set_Text_Mode(0);
}

void tarrBtn() {
    Serial.println(0x40);
    uint8_t cmd = 0x40;
    Serial1.write(cmd);
    animation1.playAnimation = true;
}

void unitBtn() {
}

void playAnimations() {
    if (animation1.playAnimation) clickAnimation1();
}

void Draw_Menu(Touch *touch) {
    touch->clearHitbox();
    uint32_t x, y, len;

    lcd.Fill_Screen(17, 17, 17);
    lcd.Set_Draw_color(235, 32, 250);
    lcd.Draw_Rectangle(0, 0, lcd.Get_Width() - 1, lcd.Get_Height() / 2 - 2);

    lcd.Set_Text_Size(2);
    lcd.Set_Text_Mode(1);
    lcd.Print_String(" Digitaalinen vaaka projekti", CENTER, lcd.Get_Height() / 4 - 1);
    lcd.Set_Text_Mode(0);

    lcd.Set_Draw_color(35, 190, 235);
    lcd.Fill_Rectangle(0, lcd.Get_Height() / 2 + 1, lcd.Get_Width() - 1, lcd.Get_Height() - 1);

    lcd.Set_Draw_color(34, 139, 34);
    lcd.Fill_Round_Rectangle(10, lcd.Get_Height() / 2 + 1 + 10, lcd.Get_Width() / 3 - 1 - 5, lcd.Get_Height() - 1 - 10, 20);
    lcd.Set_Text_Size(2);
    lcd.Set_Text_Mode(1);
    len = Pixel_srtlen("Tare", 2);
    x = String_x_pos(6, len);
    y = String_y_pos(4, 3, 2);
    lcd.Print_String("Tare", x, y);
    lcd.Set_Text_Mode(0);

    lcd.Set_Draw_color(25, 25, 112);
    lcd.Fill_Round_Rectangle(lcd.Get_Width() / 3 - 1 + 5, lcd.Get_Height() / 2 + 1 + 10, lcd.Get_Width() / 3 * 2 - 1 - 5, lcd.Get_Height() - 1 - 10, 20);
    lcd.Set_Text_Size(2);
    lcd.Set_Text_Mode(1);
    len = Pixel_srtlen("Unit", 2);
    x = String_x_pos(2, len);
    y = String_y_pos(4, 3, 2);
    lcd.Print_String("Unit", x, y);
    lcd.Set_Text_Mode(0);

    lcd.Set_Draw_color(199, 21, 133);
    lcd.Fill_Round_Rectangle(lcd.Get_Width() / 3 * 2 + 5, lcd.Get_Height() / 2 + 1 + 10, lcd.Get_Width() - 1 - 10, lcd.Get_Height() - 1 - 10, 20);
    lcd.Set_Text_Size(2);
    lcd.Set_Text_Mode(1);
    len = Pixel_srtlen("null", 2);
    x = String_x_pos(6, 5, len);
    y = String_y_pos(4, 3, 2);
    lcd.Print_String("null", x, y);
    lcd.Set_Text_Mode(0);

    touch->registerHitbox(10, lcd.Get_Height() / 2 + 1 + 10, lcd.Get_Width() / 3 - 1 - 5, lcd.Get_Height() - 1 - 10, tarrBtn);
    touch->registerHitbox(lcd.Get_Width() / 3 - 1 + 5, lcd.Get_Height() / 2 + 1 + 10, lcd.Get_Width() / 3 * 2 - 1 - 5, lcd.Get_Height() - 1 - 10, unitBtn);

    isMenuPrinted = true;
}

/*
Calculate strings lenght in pixels
str is the string for which the calculation is done
*/
uint32_t Pixel_srtlen(const char *str) {
    return strlen(str) * 6 * 1;
}

uint32_t Pixel_srtlen(const char *str, uint8_t text_size) {
    return strlen(str) * 6 * text_size;
}

/* 
Calculate srings x position in the middle of that string
screen_divisions is the number to how many groups of pixels the screen is divided
division_index is the index of the group of pixels
*/
uint32_t String_x_pos(uint32_t screen_divisions, uint32_t division_index, uint32_t string_len) {
    return (lcd.Get_Display_Width() / screen_divisions * division_index - string_len / 2);
}

uint32_t String_x_pos(uint32_t screen_divisions, uint32_t string_len) {
    return (lcd.Get_Display_Width() / screen_divisions - string_len / 2);
}

//Return the text height multiplied by text_size
uint32_t Pixel_strhgt(uint8_t text_size) {
    return 8 * text_size;
}

/* 
Calculate srings y position in the middle of that string
screen_divisions is the number to how many groups of pixels the screen is divided
division_index is the index of the group of pixels
*/
uint32_t String_y_pos(uint32_t screen_divisions, uint32_t division_index, uint8_t text_size) {
    return (lcd.Get_Display_Height() / screen_divisions * division_index - Pixel_strhgt(2) / 2 + text_size / 2 - 1);
}

uint32_t String_y_pos(uint32_t screen_divisions, uint8_t text_size) {
    return (lcd.Get_Display_Height() / screen_divisions - Pixel_strhgt(2) / 2 + text_size / 2 - 1);
}

void InitScreen() {
    animation1 = {10, lcd.Get_Height() / 2 + 1 + 10, lcd.Get_Width() / 3 - 1 - 5, lcd.Get_Height() - 1 - 10};
    animation2 = {lcd.Get_Width() / 3 - 1 + 5, lcd.Get_Height() / 2 + 1 + 10, lcd.Get_Width() / 3 * 2 - 1 - 5, lcd.Get_Height() - 1 - 10};
}