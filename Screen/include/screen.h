#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <Arduino.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>

extern LCDWIKI_KBV lcd;
extern bool isMenuPrinted;

void Draw_Menu();

uint32_t Pixel_srtlen(const char *str);
uint32_t Pixel_srtlen(const char *str, uint8_t text_size);
uint32_t String_x_pos(uint32_t screen_divisions, uint32_t division_index, uint32_t string_len);
uint32_t String_x_pos(uint32_t screen_divisions, uint32_t string_len);

uint32_t Pixel_strhgt(uint8_t text_size);
#endif