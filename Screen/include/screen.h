#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <Arduino.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>

#include "touch.h"

extern LCDWIKI_KBV lcd;
extern bool isMenuPrinted;

struct animation_t {
    int16_t x1;
    int16_t y1;
    int16_t x2;
    int16_t y2;

    uint8_t state = 0;
    bool playAnimation = false;

    animation_t() {}
    animation_t(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2) {
        x1 = X1;
        x2 = X2;
        y1 = Y1;
        y2 = Y2;
    }
};

void InitScreen();
void Draw_Menu(Touch *touch);
void playAnimations();

uint32_t Pixel_srtlen(const char *str);
uint32_t Pixel_srtlen(const char *str, uint8_t text_size);
uint32_t String_x_pos(uint32_t screen_divisions, uint32_t division_index, uint32_t string_len);
uint32_t String_x_pos(uint32_t screen_divisions, uint32_t string_len);

uint32_t Pixel_strhgt(uint8_t text_size);
uint32_t String_y_pos(uint32_t screen_divisions, uint32_t division_index, uint8_t text_size);
uint32_t String_y_pos(uint32_t screen_divisions, uint8_t text_size);
#endif  //_SCREEN_H_