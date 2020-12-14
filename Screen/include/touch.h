#ifndef _TOUCH_H_
#define _TOUCH_H_
#include <Arduino.h>
#include <LCDWIKI_KBV.h>

//Library for the touch
#include <TouchScreen.h>

#define TS_LEFT 94
#define TS_TOP 126
#define TS_RIGHT 945
#define TS_BOT 900

#define MINPRESSURE 10
#define MAXPRESSURE 1000

//x = map(p.y, TS_LEFT, TS_RIGHT, 0, lcd.get_width());
//y = map(p.x, TS_TOP, TS_BOT, 0, lcd.get_height());

//Struct for hitbox handler and cordinates
typedef struct {
    int16_t x1;
    int16_t x2;
    int16_t y1;
    int16_t y2;
    void (*func)();
} hitbox_t;

//Touch class
class Touch {
  private:
    TouchScreen sensor;
    uint8_t _xm;  //Analog pin
    uint8_t _xp;  //Digital pin
    uint8_t _ym;  //Digital pin
    uint8_t _yp;  //Analog pin

    hitbox_t *hitbox;
    size_t hitboxSize = 0;

  public:
    Touch(uint8_t XM, uint8_t YM, uint8_t XP, uint8_t YP);
    ~Touch();
    TSPoint readTouch(LCDWIKI_KBV &lcd);
    void registerHitbox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, void (*func)());
    void hitboxClicked(LCDWIKI_KBV &lcd);
    void clearHitbox();
};

#endif  //_TOUCH_H_