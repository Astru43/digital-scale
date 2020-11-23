#include "graphic.h"

#include <Arduino.h>

Graphics::Graphics(Pins pins) {
    _pins = pins;
    pinMode(_pins.LCD_CS, OUTPUT);
    pinMode(_pins.LCD_RD, OUTPUT);
    pinMode(_pins.LCD_WR, OUTPUT);
    pinMode(_pins.LCD_RST, OUTPUT);
    pinMode(_pins.LCD_RS, OUTPUT);
    for (int i = 0; i < 8; i++) {
        pinMode(_pins.LCD_DATA[i], OUTPUT);
    }
    digitalWrite(_pins.LCD_RST, HIGH);
    digitalWrite(_pins.LCD_CS, LOW);
}

void Graphics::Reset() {
    pinMode(_pins.LCD_CS, OUTPUT);
    pinMode(_pins.LCD_RD, OUTPUT);
    pinMode(_pins.LCD_WR, OUTPUT);
    pinMode(_pins.LCD_RS, OUTPUT);
    for (int i = 0; i < 8; i++) {
        pinMode(_pins.LCD_DATA[i], OUTPUT);
    }

    digitalWrite(_pins.LCD_WR, LOW);
    digitalWrite(_pins.LCD_RD, LOW);
    digitalWrite(_pins.LCD_CS, LOW);
    digitalWrite(_pins.LCD_RS, LOW);
}

void Graphics::LcdInfo(uint8_t *data, uint8_t size) {
    if (size < 3) return;
    
    uint8_t _cs = digitalPinToBitMask(_pins.LCD_CS);
    uint8_t _rd = digitalPinToBitMask(_pins.LCD_RD);
    uint8_t _wr = digitalPinToBitMask(_pins.LCD_WR);
    uint8_t _rs = digitalPinToBitMask(_pins.LCD_RS);

    PORTF = (0x00 & _cs);
    PORTF = (0x00 & _rs);
    PORTF = (0xff & _rd);
    
    PORTH |= (0xf << PH3);

    PORTF = (0xff & _wr);
    delayMicroseconds(1);
    PORTF = (0xff & _rs);

    for(int i = 0; i < 8; i++) pinMode(_pins.LCD_DATA[i], INPUT);

    PORTF = (0x00 & _rd);
    delayMicroseconds(1);
    PORTF = (0xff & _rd);
    delayMicroseconds(1);
    PORTF = (0x00 & _rd);
    delayMicroseconds(1);
    PORTF = (0xff & _rd);
    
    data[0] = (PINH % (0x3 << PH5)) >> 5;
    data[0] |= (PINE & (0x3 << PE4)) >> 2;
    data[0] |= (PING & (0x1 << PG5)) >> 1;
    data[0] |= (PINE & (0x1 << PE3)) << 2;
    data[0] |= (PINH & (0x3 << PH3)) << 5;

    
    PORTF = (0x00 & _rd);
    delayMicroseconds(1);
    PORTF = (0xff & _rd);
    
    data[1] = (PINH % (0x3 << PH5)) >> 5;
    data[1] |= (PINE & (0x3 << PE4)) >> 2;
    data[1] |= (PING & (0x1 << PG5)) >> 1;
    data[1] |= (PINE & (0x1 << PE3)) << 2;
    data[1] |= (PINH & (0x3 << PH3)) << 5;

    
    PORTF = (0x00 & _rd);
    delayMicroseconds(1);
    PORTF = (0xff & _rd);
    
    data[2] = (PINH % (0x3 << PH5)) >> 5;
    data[2] |= (PINE & (0x3 << PE4)) >> 2;
    data[2] |= (PING & (0x1 << PG5)) >> 1;
    data[2] |= (PINE & (0x1 << PE3)) << 2;
    data[2] |= (PINH & (0x3 << PH3)) << 5;

    return;
}







/*

interface pins order
b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7
8  | 9  | 2  | 3  | 4  | 5  | 6  | 7
PH5|PH6 |PE4 |PE5 |PG5 |PE3 |PH3 |PH4

*/