#pragma once

#include "../renderer.h"
#include "../rocket.h"

const int8_t stem_offsets[] PROGMEM = {
    0, 1, 2, 3, 3, 2, 1, 0, -1, -2, -3, -3, -2, -1};
const unsigned char bmp_can[] PROGMEM = {
    // 'can, 19x17px
    0x3d, 0x00, 0x00, 0x67, 0x80, 0x00, 0xc3, 0xc0, 0x00, 0x87, 0xe0, 0x00, 0x8f, 0xf0, 0x00, 0x9f,
    0xf8, 0x00, 0xff, 0xfc, 0x00, 0x7f, 0xfe, 0x00, 0xff, 0xfc, 0x00, 0x7f, 0xf8, 0x00, 0x3f, 0xf0,
    0x00, 0x1f, 0xe8, 0x00, 0x0f, 0xdc, 0x20, 0x07, 0xbe, 0x60, 0x03, 0x7f, 0xe0, 0x00, 0x00, 0x60,
    0x00, 0x00, 0x20};

const uint8_t NUM_DROPS = 80;
class PlantRenderer
    : public Renderer
{
public:
    virtual void press(bool pressed) {}
    virtual void start()
    {
        i = 0;
        for (int8_t f = 0; f < NUM_DROPS; f++)
        {
            icons[f][1] = 128;
        }
    }
    virtual void update(bool buttonHeld)
    {
        if (_elapsed < 33)
            return;
        if (buttonHeld)
            resetSleepTimer();

        float row_f = ms_to_row_f(curtime_ms, rps);

        int8_t x = (int8_t)sync_get_val(s_tracks[0], row_f);
        int8_t y = (int8_t)sync_get_val(s_tracks[1], row_f);

        _elapsed = 0;
        display.clearDisplay();
        display.drawBitmap(x, y, bmp_can, 19, 17, WHITE);

        uint8_t stem_length = (uint8_t)sync_get_val(s_tracks[2], row_f);
        for (uint8_t s = 0; s < stem_length; s++)
        {
            display.drawPixel(30 + stem_offsets[s % 13], 128 - 5 - s, WHITE);
        }

        {
            uint8_t flowerFrame = (uint8_t)sync_get_val(s_tracks[3], row_f);
            if (flowerFrame > 8)
                flowerFrame = 8;
            display.drawBitmap(24, 50, epd_flower_allArray[flowerFrame], 16, 16, WHITE);
            display.drawBitmap((int8_t)sync_get_val(s_tracks[4], row_f), (int8_t)sync_get_val(s_tracks[5], row_f), bmp_heart, HEART_WIDTH, HEART_HEIGHT, WHITE);
        }
        // j++;

        display.drawFastHLine(5, 128 - 5, 64 - 10, WHITE);

        if (buttonHeld)
        {
            icons[i][0] = 28 + random(8);
            icons[i][1] = 25;
            i = ((i + 1) % NUM_DROPS);
        }
        for (int8_t f = 0; f < NUM_DROPS; f++)
        {
            if (icons[f][1] == 123)
                {curtime_ms+=160;Serial.println(curtime_ms);}
            if (icons[f][1] < 123)
                icons[f][1] += 2;
            else
                icons[f][1] = 128;
        }
        for (int8_t f = 0; f < NUM_DROPS; f++)
        {
            display.drawPixel(icons[f][0], icons[f][1], WHITE);
        }

        display.display();
    }

protected:
    uint8_t i;
    int16_t icons[NUM_DROPS][2];
    elapsedMillis _elapsed;
};