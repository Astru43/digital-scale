#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <stdint.h>

typedef struct {
    uint8_t LCD_RST;
    uint8_t LCD_CS;
    uint8_t LCD_RS;
    uint8_t LCD_WR;
    uint8_t LCD_RD;
    uint8_t LCD_DATA[8];

    uint8_t SD_SS;
    uint8_t SD_DI;
    uint8_t SD_DO;
    uint8_t SD_SCK;
} Pins;

class Graphics {
  private:
    Pins _pins;
    uint8_t csSet;
    uint8_t rdSet;
    uint8_t wrSet;
    uint8_t rsSet;

    uint8_t csUnset;
    uint8_t rdUnset;
    uint8_t wrUnset;
    uint8_t rsUnset;

    inline void Data();
    inline void Command();
    inline void Write8(uint8_t cmd);
    inline void Read8(uint8_t *data);
    uint16_t ReadReg(uint16_t reg, uint8_t index);

  public:
    Graphics() = default;
    Graphics(Pins pins);
    ~Graphics() = default;

    void LcdInfo(uint8_t *data, uint8_t size);
    inline void WriteCmd8(uint8_t cmd);
};

#endif