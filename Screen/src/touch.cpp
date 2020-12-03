#include "touch.h"

Touch::Touch(uint8_t XM, uint8_t YM, uint8_t XP, uint8_t YP) : sensor(XP, YP, XM, YM, 300) {
    _xm = XM;
    _ym = YM;
    _xp = XM;
    _yp = YP;
}

Touch::~Touch() {
}

TSPoint Touch::readTouch() {
    TSPoint p = sensor.getPoint();
    pinMode(_xm, OUTPUT);
    pinMode(_ym, OUTPUT);
    pinMode(_xp, OUTPUT);
    pinMode(_yp, OUTPUT);
    return p;
}