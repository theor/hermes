//
// Created by theor on 2022-07-31.
//

#ifndef HERMES_SPRITE_H
#define HERMES_SPRITE_H

#include <TFT_eSPI.h>

class Sprite : public TFT_eSprite
{
public:
    Sprite(TFT_eSPI *tft);

    void pushBitmap1bpp(int32_t x, int32_t y, int32_t w, int32_t h, const uint8_t *data, uint16_t fgColor, uint16_t bgColor, bool transparent = false);
    void pushBitmap4bpp(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data, uint16_t* colorMap);

    TFT_eSPI* getScreen() { return _screen;}
protected:
    TFT_eSPI* _screen;
};


#endif //HERMES_SPRITE_H
