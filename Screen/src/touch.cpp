#include "touch.h"

Touch::Touch(uint8_t XM, uint8_t YM, uint8_t XP, uint8_t YP) : sensor(XP, YP, XM, YM, 300) {
    _xm = XM;
    _ym = YM;
    _xp = XM;
    _yp = YP;
}

//Touch destructor
Touch::~Touch() {
    if (hitboxSize != 0) delete hitbox;
}

//Read touch sensor and map the value to screen pixels
TSPoint Touch::readTouch(LCDWIKI_KBV &lcd) {
    TSPoint p = sensor.getPoint();
    pinMode(_xm, OUTPUT);
    pinMode(_ym, OUTPUT);
    pinMode(_xp, OUTPUT);
    pinMode(_yp, OUTPUT);

    uint16_t tmp = p.y;
    p.y = map(p.x, TS_TOP, TS_BOT, 0, lcd.Get_Height());
    p.x = map(tmp, TS_LEFT, TS_RIGHT, 0, lcd.Get_Width());
    return p;
}

//Add hitbox to the hitbox array of hitboxies to check for touch
void Touch::registerHitbox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, void (*func)()) {
    if (hitboxSize == 0) {
        //Initialize new hitbox array
        hitbox = new hitbox_t[++hitboxSize];
        Serial.println(hitboxSize);
    } else {
        //Increment hitbox size to fit more hitbox structs
        hitbox_t *tmp = new hitbox_t[++hitboxSize];
        for (uint32_t i = 0; i < hitboxSize - 1; i++) {
            tmp[i] = hitbox[i];
        }
        delete hitbox;
        hitbox = tmp;
        Serial.println(hitboxSize);
    }

    //Map hitbox cordinates so that x1 is smaller than x2
    if (x1 < x2 && y1 < y2) {
        hitbox[hitboxSize - 1] = {x1, x2, y1, y2, func};
    } else if (x1 > x2 && y1 < y2) {
        hitbox[hitboxSize - 1] = {x2, x1, y1, y2, func};
    } else if (x1 < x2 && y1 > y2) {
        hitbox[hitboxSize - 1] = {x1, x2, y2, y1, func};
    } else {
        hitbox[hitboxSize - 1] = {x2, x1, y2, y1, func};
    }
}

//Check for hitbox hit in any hitbox included in the hitbox array
void Touch::hitboxClicked(LCDWIKI_KBV &lcd) {
    TSPoint p = readTouch(lcd);

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        //Serial.print(p.x);
        //Serial.print(" | ");
        //Serial.println(p.y);
        for (uint32_t i = 0; i < hitboxSize; i++) {
            hitbox_t hit = hitbox[i];

            if (hit.x1 < p.x && hit.x2 > p.x && hit.y1 < p.y && hit.y2 > p.y) {
                hit.func();
                break;
            }
        }
    }
}

//Delete the hitbox array
void Touch::clearHitbox() {
    if (hitboxSize != 0) {
        delete hitbox;
        hitboxSize = 0;
    }
}