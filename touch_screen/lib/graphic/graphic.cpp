#include "graphic.h"

#include <Arduino.h>
#include <wiring_private.h>
#include <pins_arduino.h>

Graphics::Graphics(Pins pins) {
    _pins = pins;
    pinMode(_pins.LCD_CS, OUTPUT);
    pinMode(_pins.LCD_RD, OUTPUT);
    pinMode(_pins.LCD_WR, OUTPUT);
    pinMode(_pins.LCD_RS, OUTPUT);

    csSet = digitalPinToBitMask(_pins.LCD_CS);
    rdSet = digitalPinToBitMask(_pins.LCD_RD);
    wrSet = digitalPinToBitMask(_pins.LCD_WR);
    rsSet = digitalPinToBitMask(_pins.LCD_RS);
    csUnset = ~csSet;
    rdUnset = ~rdSet;
    wrUnset = ~wrSet;
    rsUnset = ~rsSet;

    digitalWrite(_pins.LCD_RST, HIGH);
    pinMode(_pins.LCD_RST, OUTPUT);
    ;
}

void Graphics::LcdInfo(uint8_t *data, uint8_t size) {
    if (size < 3) return;
    PORTF &= csUnset;
    uint16_t tmp = ReadReg(0x04, 0);
    uint16_t tmp1 = ReadReg(0x04, 1);

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

uint16_t Graphics::ReadReg(uint16_t reg, uint8_t index) {
    Command();
    Write8(reg >> 8);
    Write8(reg);
    Data();
}

inline void Graphics::Write8(uint8_t cmd) {
    
}

inline void Graphics::Command() {
    PORTF &= rsUnset;
}

inline void Graphics::Data() {
    PORTF &= rsSet;
}

/*

interface pins order
b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7
8  | 9  | 2  | 3  | 4  | 5  | 6  | 7
PH5|PH6 |PE4 |PE5 |PG5 |PE3 |PH3 |PH4




data[0] = (PINH % (0x3 << PH5)) >> 5;
    data[0] |= (PINE & (0x3 << PE4)) >> 2;
    data[0] |= (PING & (0x1 << PG5)) >> 1;
    data[0] |= (PINE & (0x1 << PE3)) << 2;
    data[0] |= (PINH & (0x3 << PH3)) << 5;

*/