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
    void Reset();

  public:
    Graphics() = default;
    Graphics(Pins pins);
    ~Graphics() = default;

    void LcdInfo(uint8_t *data, uint8_t size);
};

#endif