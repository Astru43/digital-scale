#ifndef _TOUCH_H_
#define _TOUCH_H_
#include <Arduino.h>
#include <LCDWIKI_KBV.h>
#include <TouchScreen.h>

#define TS_LEFT 94
#define TS_TOP 130
#define TS_RIGHT 945
#define TS_BOT 822

#define MINPRESSURE 10
#define MAXPRESSURE 1000
/*
#define TS_LEFT 956
#define TS_TOP 804
#define TS_RIGHT 119
#define TS_BOT 237
*/
//x = map(p.y, TS_LEFT, TS_RIGHT, 0, lcd.get_width());
//y = map(p.x, TS_TOP, TS_BOT, 0, lcd.get_height());

typedef struct {
    uint16_t x1;
    uint16_t x2;
    uint16_t y1;
    uint16_t y2;
    void (*func)();
} hitbox_t;

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
    void registerHitbox(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, void (*func)());
    void hitboxClicked(LCDWIKI_KBV &lcd);
};

#endif  //_TOUCH_H_