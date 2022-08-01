//
// Created by theor on 2022-07-31.
//

#include "Sprite.h"

// Clipping macro for pushImage
#define PI_CLIP                                        \
  if (_vpOoB) return;                                  \
  x+= _xDatum;                                         \
  y+= _yDatum;                                         \
                                                       \
  if ((x >= _vpW) || (y >= _vpH)) return;              \
                                                       \
  int32_t dx = 0;                                      \
  int32_t dy = 0;                                      \
  int32_t dw = w;                                      \
  int32_t dh = h;                                      \
                                                       \
  if (x < _vpX) { dx = _vpX - x; dw -= dx; x = _vpX; } \
  if (y < _vpY) { dy = _vpY - y; dh -= dy; y = _vpY; } \
                                                       \
  if ((x + dw) > _vpW ) dw = _vpW - x;                 \
  if ((y + dh) > _vpH ) dh = _vpH - y;                 \
                                                       \
  if (dw < 1 || dh < 1) return;

void Sprite::pushBitmap1bpp(int32_t x, int32_t y, int32_t w, int32_t h, const uint8_t *data, uint16_t fgColor, uint16_t bgColor, bool transparent)
{
    PI_CLIP;

    uint32_t ww =  (w+7)>>3; // Width of source image line in bytes
    uint8_t *ptr = (uint8_t *)data;
    for (int32_t yp = dy;  yp < dy + dh; yp++)
    {
        uint32_t yw = yp * ww;              // Byte starting the line containing source pixel
        int32_t ox = x;
        for (int32_t xp = dx; xp < dx + dw; xp++)
        {
            uint16_t readPixel = (ptr[(xp>>3) + yw] & (0x80 >> (xp & 0x7)) );
            if(readPixel)
                drawPixel(ox, y, fgColor);
            else if(!transparent)
                drawPixel(ox, y, bgColor);
            ox++;
        }
        y++;
    }

}
void Sprite::pushBitmap4bpp(int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data, uint16_t* colorMap){

}

Sprite::Sprite(TFT_eSPI *tft) : TFT_eSprite(tft), _screen(tft) {}
