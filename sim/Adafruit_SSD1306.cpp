//
// Created by theor on 2022-07-29.
//

#include <cstdlib>
#include <cstring>
#include "Arduino.h"
#include "Adafruit_SSD1306.h"


#define splash1_width  82
#define splash1_height 64

const uint8_t PROGMEM splash1_data[] = {
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000001,0b10000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000011,0b10000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000111,0b11000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000111,0b11000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00001111,0b11000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00011111,0b11100000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00011111,0b11100000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00111111,0b11100000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00111111,0b11110000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b01111111,0b11110000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00011111,0b11111000,0b01111111,0b11110000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00111111,0b11111110,0b01111111,0b11110000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00111111,0b11111111,0b01111111,0b11110000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00011111,0b11111111,0b11111011,0b11100000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00001111,0b11111111,0b11111001,0b11111111,0b11000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00001111,0b11111111,0b11111001,0b11111111,0b11111000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000111,0b11111111,0b11110001,0b11111111,0b11111111,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000011,0b11111100,0b01110011,0b11111111,0b11111111,0b10000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000001,0b11111110,0b00111111,0b11111111,0b11111111,0b10000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b00011110,0b00001111,0b11111111,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b01111111,0b11111110,0b00011111,0b11111100,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00111111,0b11111111,0b11111111,0b11111000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00001111,0b11011111,0b11111111,0b11100000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00011111,0b00011001,0b11111111,0b11000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00111111,0b00111100,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b01111110,0b01111100,0b11111000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b01111111,0b11111110,0b01111100,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b11111111,0b11111100,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b11111111,0b11111110,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b11111111,0b11111110,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000001,0b11111111,0b11101111,0b11111110,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000001,0b11111111,0b11001111,0b11111110,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000011,0b11111111,0b00000111,0b11111110,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000011,0b11111100,0b00000111,0b11111110,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000011,0b11110000,0b00000011,0b11111110,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000001,0b10000000,0b00000000,0b11111110,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b01111110,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00111110,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00001100,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b00000111,0b10000000,0b00000000,0b11111100,0b00000000,0b00000000,0b00000011,0b11000000,0b00000000,
0b00000000,0b00000000,0b00000111,0b10000000,0b00000001,0b11111100,0b00000000,0b00000000,0b00000011,0b11000000,0b00000000,
0b00000000,0b00000000,0b00000111,0b10000000,0b00000001,0b11111100,0b00000000,0b00000000,0b00000011,0b11000000,0b00000000,
0b00000000,0b00000000,0b00000111,0b10000000,0b00000001,0b11100000,0b00000000,0b00000000,0b00000000,0b00011110,0b00000000,
0b00000000,0b00000000,0b00000111,0b10000000,0b00000001,0b11100000,0b00000000,0b00000000,0b00000000,0b00011110,0b00000000,
0b01111111,0b11100011,0b11110111,0b10011111,0b11111001,0b11111101,0b11100111,0b01111000,0b01111011,0b11011111,0b11000000,
0b11111111,0b11110111,0b11111111,0b10111111,0b11111101,0b11111101,0b11111111,0b01111000,0b01111011,0b11011111,0b11000000,
0b11111111,0b11110111,0b11111111,0b10111111,0b11111101,0b11111101,0b11111111,0b01111000,0b01111011,0b11011111,0b11000000,
0b11110000,0b11110111,0b10000111,0b10111100,0b00111101,0b11100001,0b11111111,0b01111000,0b01111011,0b11011110,0b00000000,
0b11110000,0b11110111,0b10000111,0b10111100,0b00111101,0b11100001,0b11110000,0b01111000,0b01111011,0b11011110,0b00000000,
0b00000000,0b11110111,0b10000111,0b10000000,0b00111101,0b11100001,0b11100000,0b01111000,0b01111011,0b11011110,0b00000000,
0b01111111,0b11110111,0b10000111,0b10011111,0b11111101,0b11100001,0b11100000,0b01111000,0b01111011,0b11011110,0b00000000,
0b11111111,0b11110111,0b10000111,0b10111111,0b11111101,0b11100001,0b11100000,0b01111000,0b01111011,0b11011110,0b00000000,
0b11110000,0b11110111,0b10000111,0b10111100,0b00111101,0b11100001,0b11100000,0b01111000,0b01111011,0b11011110,0b00000000,
0b11110000,0b11110111,0b10000111,0b10111100,0b00111101,0b11100001,0b11100000,0b01111000,0b01111011,0b11011110,0b00000000,
0b11110000,0b11110111,0b10000111,0b10111100,0b00111101,0b11100001,0b11100000,0b01111000,0b01111011,0b11011110,0b00000000,
0b11111111,0b11110111,0b11111111,0b10111111,0b11111101,0b11100001,0b11100000,0b01111111,0b11111011,0b11011111,0b11000000,
0b11111111,0b11110111,0b11111111,0b10111111,0b11111101,0b11100001,0b11100000,0b01111111,0b11111011,0b11011111,0b11000000,
0b01111100,0b11110011,0b11110011,0b10011111,0b00111101,0b11100001,0b11100000,0b00111110,0b01111011,0b11001111,0b11000000,
0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11000000,
0b11111111,0b11111111,0b11111111,0b11111111,0b11111101,0b01101000,0b11011011,0b00010001,0b00011010,0b00110001,0b11000000,
0b11111111,0b11111111,0b11111111,0b11111111,0b11111101,0b00101011,0b01011010,0b11111011,0b01101010,0b11101111,0b11000000,
0b11111111,0b11111111,0b11111111,0b11111111,0b11111101,0b01001011,0b01011011,0b00111011,0b00011010,0b00110011,0b11000000,
0b11111111,0b11111111,0b11111111,0b11111111,0b11111101,0b01101011,0b01011011,0b11011011,0b01101010,0b11111101,0b11000000,
};

#define splash2_width  115
#define splash2_height 32

const uint8_t PROGMEM splash2_data[] = {
0b00000000,0b00000000,0b01100000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000000,0b11100000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000001,0b11100000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000001,0b11110000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000011,0b11110000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000111,0b11110000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00000111,0b11111000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00000000,0b00001111,0b11111000,0b00000000,0b00000000,0b00000000,0b00000011,0b11000000,0b00000000,0b01111110,0b00000000,0b00000000,0b00000001,0b11100000,0b00000000,
0b01111111,0b00001111,0b11111000,0b00000000,0b00000000,0b00000000,0b00000011,0b11000000,0b00000000,0b11111110,0b00000000,0b00000000,0b00000001,0b11100000,0b00000000,
0b11111111,0b11101111,0b11111000,0b00000000,0b00000000,0b00000000,0b00000011,0b11000000,0b00000000,0b11111110,0b00000000,0b00000000,0b00000001,0b11100000,0b00000000,
0b11111111,0b11111111,0b11111000,0b00000000,0b00000000,0b00000000,0b00000011,0b11000000,0b00000000,0b11110000,0b00000000,0b00000000,0b00000000,0b00001111,0b00000000,
0b01111111,0b11111110,0b01111111,0b11000000,0b00000000,0b00000000,0b00000011,0b11000000,0b00000000,0b11110000,0b00000000,0b00000000,0b00000000,0b00001111,0b00000000,
0b00111111,0b11111110,0b01111111,0b11111000,0b00111111,0b11110001,0b11111011,0b11001111,0b11111100,0b11111110,0b11110011,0b10111100,0b00111101,0b11101111,0b11100000,
0b00011111,0b11111110,0b01111111,0b11111111,0b01111111,0b11111011,0b11111111,0b11011111,0b11111110,0b11111110,0b11111111,0b10111100,0b00111101,0b11101111,0b11100000,
0b00011111,0b11000110,0b11111111,0b11111111,0b01111111,0b11111011,0b11111111,0b11011111,0b11111110,0b11111110,0b11111111,0b10111100,0b00111101,0b11101111,0b11100000,
0b00001111,0b11100011,0b11000111,0b11111110,0b01111000,0b01111011,0b11000011,0b11011110,0b00011110,0b11110000,0b11111111,0b10111100,0b00111101,0b11101111,0b00000000,
0b00000111,0b11111111,0b10000111,0b11111100,0b01111000,0b01111011,0b11000011,0b11011110,0b00011110,0b11110000,0b11111000,0b00111100,0b00111101,0b11101111,0b00000000,
0b00000001,0b11111111,0b11111111,0b11110000,0b00000000,0b01111011,0b11000011,0b11000000,0b00011110,0b11110000,0b11110000,0b00111100,0b00111101,0b11101111,0b00000000,
0b00000001,0b11110011,0b01111111,0b11100000,0b00111111,0b11111011,0b11000011,0b11001111,0b11111110,0b11110000,0b11110000,0b00111100,0b00111101,0b11101111,0b00000000,
0b00000011,0b11100011,0b00111111,0b10000000,0b01111111,0b11111011,0b11000011,0b11011111,0b11111110,0b11110000,0b11110000,0b00111100,0b00111101,0b11101111,0b00000000,
0b00000111,0b11100111,0b00111100,0b00000000,0b01111000,0b01111011,0b11000011,0b11011110,0b00011110,0b11110000,0b11110000,0b00111100,0b00111101,0b11101111,0b00000000,
0b00000111,0b11111111,0b10111110,0b00000000,0b01111000,0b01111011,0b11000011,0b11011110,0b00011110,0b11110000,0b11110000,0b00111100,0b00111101,0b11101111,0b00000000,
0b00000111,0b11111111,0b11111110,0b00000000,0b01111000,0b01111011,0b11000011,0b11011110,0b00011110,0b11110000,0b11110000,0b00111100,0b00111101,0b11101111,0b00000000,
0b00001111,0b11111111,0b11111110,0b00000000,0b01111111,0b11111011,0b11111111,0b11011111,0b11111110,0b11110000,0b11110000,0b00111111,0b11111101,0b11101111,0b11100000,
0b00001111,0b11111111,0b11111111,0b00000000,0b01111111,0b11111011,0b11111111,0b11011111,0b11111110,0b11110000,0b11110000,0b00111111,0b11111101,0b11101111,0b11100000,
0b00001111,0b11111001,0b11111111,0b00000000,0b00111110,0b01111001,0b11111001,0b11001111,0b10011110,0b11110000,0b11110000,0b00011111,0b00111101,0b11100111,0b11100000,
0b00011111,0b11110001,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
0b00011111,0b10000000,0b11111111,0b00000000,0b01111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11100000,
0b00011100,0b00000000,0b01111111,0b00000000,0b01111111,0b11111111,0b11111111,0b11111111,0b11111110,0b10110100,0b01101101,0b10001000,0b10001101,0b00011000,0b11100000,
0b00000000,0b00000000,0b00011111,0b00000000,0b01111111,0b11111111,0b11111111,0b11111111,0b11111110,0b10010101,0b10101101,0b01111101,0b10110101,0b01110111,0b11100000,
0b00000000,0b00000000,0b00001111,0b00000000,0b01111111,0b11111111,0b11111111,0b11111111,0b11111110,0b10100101,0b10101101,0b10011101,0b10001101,0b00011001,0b11100000,
0b00000000,0b00000000,0b00000110,0b00000000,0b01111111,0b11111111,0b11111111,0b11111111,0b11111110,0b10110101,0b10101101,0b11101101,0b10110101,0b01111110,0b11100000,
};


#define ssd1306_swap(a, b)                                                     \
  (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))) ///< No-temp-var swap operation

Adafruit_SSD1306::Adafruit_SSD1306(uint8_t w, uint8_t h)
: Adafruit_GFX(w, h)
{

}

Adafruit_SSD1306::~Adafruit_SSD1306(void) {
    if (buffer) {
        free(buffer);
        buffer = NULL;
    }
}

bool Adafruit_SSD1306::begin()
{

    if ((!buffer) && !(buffer = (uint8_t *) malloc(WIDTH * ((HEIGHT + 7) / 8))))
        return false;

    clearDisplay();

#ifndef SSD1306_NO_SPLASH
    if (HEIGHT > 32)
    {
        drawBitmap((WIDTH - splash1_width) / 2, (HEIGHT - splash1_height) / 2,
                   splash1_data, splash1_width, splash1_height, 1);
    }
    else
    {
        drawBitmap((WIDTH - splash2_width) / 2, (HEIGHT - splash2_height) / 2,
                   splash2_data, splash2_width, splash2_height, 1);
    }
#endif
    contrast = 0x8F;


    if ((WIDTH == 128) && (HEIGHT == 32))
    {
        contrast = 0x8F;
    }
    else if ((WIDTH == 128) && (HEIGHT == 64))
    {
        contrast = (vccstate == SSD1306_EXTERNALVCC) ? 0x9F : 0xCF;
    }
    else if ((WIDTH == 96) && (HEIGHT == 16))
    {
        contrast = (vccstate == SSD1306_EXTERNALVCC) ? 0x10 : 0xAF;
    }
    else
    {
        // Other screen varieties -- TBD
    }


    return true; // Success
}



// DRAWING FUNCTIONS -------------------------------------------------------

/*!
    @brief  Set/clear/invert a single pixel. This is also invoked by the
            Adafruit_GFX library in generating many higher-level graphics
            primitives.
    @param  x
            Column of display -- 0 at left to (screen width - 1) at right.
    @param  y
            Row of display -- 0 at top to (screen height -1) at bottom.
    @param  color
            Pixel color, one of: SSD1306_BLACK, SSD1306_WHITE or
            SSD1306_INVERSE.
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void Adafruit_SSD1306::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if ((x >= 0) && (x < width()) && (y >= 0) && (y < height())) {
        // Pixel is in-bounds. Rotate coordinates if needed.
        switch (getRotation()) {
            case 1:
                ssd1306_swap(x, y);
                x = WIDTH - x - 1;
                break;
            case 2:
                x = WIDTH - x - 1;
                y = HEIGHT - y - 1;
                break;
            case 3:
                ssd1306_swap(x, y);
                y = HEIGHT - y - 1;
                break;
        }
        switch (color) {
            case SSD1306_WHITE:
                buffer[x + (y / 8) * WIDTH] |= (1 << (y & 7));
                break;
            case SSD1306_BLACK:
                buffer[x + (y / 8) * WIDTH] &= ~(1 << (y & 7));
                break;
            case SSD1306_INVERSE:
                buffer[x + (y / 8) * WIDTH] ^= (1 << (y & 7));
                break;
        }
    }
}

/*!
    @brief  Clear contents of display buffer (set all pixels to off).
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void Adafruit_SSD1306::clearDisplay(void) {
    memset(buffer, 0, WIDTH * ((HEIGHT + 7) / 8));
}

/*!
    @brief  Draw a horizontal line. This is also invoked by the Adafruit_GFX
            library in generating many higher-level graphics primitives.
    @param  x
            Leftmost column -- 0 at left to (screen width - 1) at right.
    @param  y
            Row of display -- 0 at top to (screen height -1) at bottom.
    @param  w
            Width of line, in pixels.
    @param  color
            Line color, one of: SSD1306_BLACK, SSD1306_WHITE or SSD1306_INVERSE.
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void Adafruit_SSD1306::drawFastHLine(int16_t x, int16_t y, int16_t w,
                                     uint16_t color) {
    bool bSwap = false;
    switch (rotation) {
        case 1:
            // 90 degree rotation, swap x & y for rotation, then invert x
            bSwap = true;
            ssd1306_swap(x, y);
            x = WIDTH - x - 1;
            break;
        case 2:
            // 180 degree rotation, invert x and y, then shift y around for height.
            x = WIDTH - x - 1;
            y = HEIGHT - y - 1;
            x -= (w - 1);
            break;
        case 3:
            // 270 degree rotation, swap x & y for rotation,
            // then invert y and adjust y for w (not to become h)
            bSwap = true;
            ssd1306_swap(x, y);
            y = HEIGHT - y - 1;
            y -= (w - 1);
            break;
    }

    if (bSwap)
        drawFastVLineInternal(x, y, w, color);
    else
        drawFastHLineInternal(x, y, w, color);
}

/*!
    @brief  Draw a horizontal line with a width and color. Used by public
   methods drawFastHLine,drawFastVLine
        @param x
                   Leftmost column -- 0 at left to (screen width - 1) at right.
        @param y
                   Row of display -- 0 at top to (screen height -1) at bottom.
        @param w
                   Width of line, in pixels.
        @param color
               Line color, one of: SSD1306_BLACK, SSD1306_WHITE or
   SSD1306_INVERSE.
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void Adafruit_SSD1306::drawFastHLineInternal(int16_t x, int16_t y, int16_t w,
                                             uint16_t color) {

    if ((y >= 0) && (y < HEIGHT)) { // Y coord in bounds?
        if (x < 0) {                  // Clip left
            w += x;
            x = 0;
        }
        if ((x + w) > WIDTH) { // Clip right
            w = (WIDTH - x);
        }
        if (w > 0) { // Proceed only if width is positive
            uint8_t *pBuf = &buffer[(y / 8) * WIDTH + x], mask = 1 << (y & 7);
            switch (color) {
                case SSD1306_WHITE:
                    while (w--) {
                        *pBuf++ |= mask;
                    };
                    break;
                case SSD1306_BLACK:
                    mask = ~mask;
                    while (w--) {
                        *pBuf++ &= mask;
                    };
                    break;
                case SSD1306_INVERSE:
                    while (w--) {
                        *pBuf++ ^= mask;
                    };
                    break;
            }
        }
    }
}

/*!
    @brief  Draw a vertical line. This is also invoked by the Adafruit_GFX
            library in generating many higher-level graphics primitives.
    @param  x
            Column of display -- 0 at left to (screen width -1) at right.
    @param  y
            Topmost row -- 0 at top to (screen height - 1) at bottom.
    @param  h
            Height of line, in pixels.
    @param  color
            Line color, one of: SSD1306_BLACK, SSD1306_WHITE or SSD1306_INVERSE.
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void Adafruit_SSD1306::drawFastVLine(int16_t x, int16_t y, int16_t h,
                                     uint16_t color) {
    bool bSwap = false;
    switch (rotation) {
        case 1:
            // 90 degree rotation, swap x & y for rotation,
            // then invert x and adjust x for h (now to become w)
            bSwap = true;
            ssd1306_swap(x, y);
            x = WIDTH - x - 1;
            x -= (h - 1);
            break;
        case 2:
            // 180 degree rotation, invert x and y, then shift y around for height.
            x = WIDTH - x - 1;
            y = HEIGHT - y - 1;
            y -= (h - 1);
            break;
        case 3:
            // 270 degree rotation, swap x & y for rotation, then invert y
            bSwap = true;
            ssd1306_swap(x, y);
            y = HEIGHT - y - 1;
            break;
    }

    if (bSwap)
        drawFastHLineInternal(x, y, h, color);
    else
        drawFastVLineInternal(x, y, h, color);
}

/*!
    @brief  Draw a vertical line with a width and color. Used by public method
   drawFastHLine,drawFastVLine
        @param x
                   Leftmost column -- 0 at left to (screen width - 1) at right.
        @param __y
                   Row of display -- 0 at top to (screen height -1) at bottom.
        @param __h height of the line in pixels
        @param color
                   Line color, one of: SSD1306_BLACK, SSD1306_WHITE or
   SSD1306_INVERSE.
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void Adafruit_SSD1306::drawFastVLineInternal(int16_t x, int16_t __y,
                                             int16_t __h, uint16_t color) {

    if ((x >= 0) && (x < WIDTH)) { // X coord in bounds?
        if (__y < 0) {               // Clip top
            __h += __y;
            __y = 0;
        }
        if ((__y + __h) > HEIGHT) { // Clip bottom
            __h = (HEIGHT - __y);
        }
        if (__h > 0) { // Proceed only if height is now positive
            // this display doesn't need ints for coordinates,
            // use local byte registers for faster juggling
            uint8_t y = __y, h = __h;
            uint8_t *pBuf = &buffer[(y / 8) * WIDTH + x];

            // do the first partial byte, if necessary - this requires some masking
            uint8_t mod = (y & 7);
            if (mod) {
                // mask off the high n bits we want to set
                mod = 8 - mod;
                // note - lookup table results in a nearly 10% performance
                // improvement in fill* functions
                // uint8_t mask = ~(0xFF >> mod);
                static const uint8_t PROGMEM premask[8] = {0x00, 0x80, 0xC0, 0xE0,
                                                           0xF0, 0xF8, 0xFC, 0xFE};
                uint8_t mask = pgm_read_byte(&premask[mod]);
                // adjust the mask if we're not going to reach the end of this byte
                if (h < mod)
                    mask &= (0XFF >> (mod - h));

                switch (color) {
                    case SSD1306_WHITE:
                        *pBuf |= mask;
                        break;
                    case SSD1306_BLACK:
                        *pBuf &= ~mask;
                        break;
                    case SSD1306_INVERSE:
                        *pBuf ^= mask;
                        break;
                }
                pBuf += WIDTH;
            }

            if (h >= mod) { // More to go?
                h -= mod;
                // Write solid bytes while we can - effectively 8 rows at a time
                if (h >= 8) {
                    if (color == SSD1306_INVERSE) {
                        // separate copy of the code so we don't impact performance of
                        // black/white write version with an extra comparison per loop
                        do {
                            *pBuf ^= 0xFF; // Invert byte
                            pBuf += WIDTH; // Advance pointer 8 rows
                            h -= 8;        // Subtract 8 rows from height
                        } while (h >= 8);
                    } else {
                        // store a local value to work with
                        uint8_t val = (color != SSD1306_BLACK) ? 255 : 0;
                        do {
                            *pBuf = val;   // Set byte
                            pBuf += WIDTH; // Advance pointer 8 rows
                            h -= 8;        // Subtract 8 rows from height
                        } while (h >= 8);
                    }
                }

                if (h) { // Do the final partial byte, if necessary
                    mod = h & 7;
                    // this time we want to mask the low bits of the byte,
                    // vs the high bits we did above
                    // uint8_t mask = (1 << mod) - 1;
                    // note - lookup table results in a nearly 10% performance
                    // improvement in fill* functions
                    static const uint8_t PROGMEM postmask[8] = {0x00, 0x01, 0x03, 0x07,
                                                                0x0F, 0x1F, 0x3F, 0x7F};
                    uint8_t mask = pgm_read_byte(&postmask[mod]);
                    switch (color) {
                        case SSD1306_WHITE:
                            *pBuf |= mask;
                            break;
                        case SSD1306_BLACK:
                            *pBuf &= ~mask;
                            break;
                        case SSD1306_INVERSE:
                            *pBuf ^= mask;
                            break;
                    }
                }
            }
        } // endif positive height
    }   // endif x in bounds
}

/*!
    @brief  Return color of a single pixel in display buffer.
    @param  x
            Column of display -- 0 at left to (screen width - 1) at right.
    @param  y
            Row of display -- 0 at top to (screen height -1) at bottom.
    @return true if pixel is set (usually SSD1306_WHITE, unless display invert
   mode is enabled), false if clear (SSD1306_BLACK).
    @note   Reads from buffer contents; may not reflect current contents of
            screen if display() has not been called.
*/
bool Adafruit_SSD1306::getPixel(int16_t x, int16_t y) {
    if ((x >= 0) && (x < width()) && (y >= 0) && (y < height())) {
        // Pixel is in-bounds. Rotate coordinates if needed.
        switch (getRotation()) {
            case 1:
                ssd1306_swap(x, y);
                x = WIDTH - x - 1;
                break;
            case 2:
                x = WIDTH - x - 1;
                y = HEIGHT - y - 1;
                break;
            case 3:
                ssd1306_swap(x, y);
                y = HEIGHT - y - 1;
                break;
        }
        return (buffer[x + (y / 8) * WIDTH] & (1 << (y & 7)));
    }
    return false; // Pixel out of bounds
}

/*!
    @brief  Get base address of display buffer for direct reading or writing.
    @return Pointer to an unsigned 8-bit array, column-major, columns padded
            to full byte boundary if needed.
*/
uint8_t *Adafruit_SSD1306::getBuffer(void) { return buffer; }

// REFRESH DISPLAY ---------------------------------------------------------

/*!
    @brief  Push data currently in RAM to SSD1306 display.
    @return None (void).
    @note   Drawing operations are not visible until this function is
            called. Call after each graphics command, or after a whole set
            of graphics commands, as best needed by one's own application.
*/
void Adafruit_SSD1306::display(void) {}
void Adafruit_SSD1306::invertDisplay(bool i) { this->inverted = i; }
void Adafruit_SSD1306::dim(bool dim) {}