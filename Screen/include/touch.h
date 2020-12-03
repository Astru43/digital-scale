#ifndef _TOUCH_H_
#define _TOUCH_H_
#include <Arduino.h>
#include <TouchScreen.h>

#define TS_LEFT 94
#define TS_TOP 235
#define TS_RIGHT 915
#define TS_BOT 742

/*
#define TS_LEFT 956
#define TS_TOP 804
#define TS_RIGHT 119
#define TS_BOT 237
*/
//x = map(p.y, TS_LEFT, TS_RIGHT, 0, lcd.get_width());
//y = map(p.x, TS_TOP, BOT, 0, lcd.get_height());

class Touch
{
private:
    uint8_t _xm; //Analog pin
    uint8_t _xp; //Digital pin
    uint8_t _ym; //Digital pin
    uint8_t _yp; //Analog pin

    TouchScreen sensor;
public:
    Touch(uint8_t XM, uint8_t YM, uint8_t XP, uint8_t YP);
    ~Touch();
    TSPoint readTouch();
    
};

#endif //_TOUCH_H_