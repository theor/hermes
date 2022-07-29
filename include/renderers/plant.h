#pragma once

#include "../renderer.h"
#include "../rocket.h"

namespace Plant
{
    const int8_t stem_offsets[] PROGMEM = {
            0, 1, 2, 3, 3, 2, 1, 0, -1, -2, -3, -3, -2, -1
    };
    const unsigned char bmp_can[] PROGMEM = {
            // 'can, 19x17px
            0x3d, 0x00, 0x00, 0x67, 0x80, 0x00, 0xc3, 0xc0, 0x00, 0x87, 0xe0, 0x00, 0x8f, 0xf0, 0x00, 0x9f,
            0xf8, 0x00, 0xff, 0xfc, 0x00, 0x7f, 0xfe, 0x00, 0xff, 0xfc, 0x00, 0x7f, 0xf8, 0x00, 0x3f, 0xf0,
            0x00, 0x1f, 0xe8, 0x00, 0x0f, 0xdc, 0x20, 0x07, 0xbe, 0x60, 0x03, 0x7f, 0xe0, 0x00, 0x00, 0x60,
            0x00, 0x00, 0x20
    };

#define TRACK_LOOP 0
#define TRACK_LOOP_PLAY 1
#define TRACK_CAN_X 2
#define TRACK_CAN_Y 3
#define TRACK_FLOWER_STEM 4
#define TRACK_FLOWER_OPENING 5
#define TRACK_HEART_X 6
#define TRACK_HEART_Y 7

    const uint8_t NUM_DROPS = 80;

    class PlantRenderer
            : public Renderer
    {
    protected:
        uint8_t i;
        int16_t icons[NUM_DROPS][2];
        elapsedMillis _elapsed;
        const struct sync_track *s_tracks[8];
    public:
        virtual void press(bool pressed)
        {
//            if (pressed)
//            else
//                display.stopscroll();
        }

        const char *getPrefix() override
        {
            return "plant";
        }

        virtual void initTracks(sync_device *device)
        {
            s_tracks[TRACK_LOOP] = sync_get_track(device, "loop#goto");
            s_tracks[TRACK_LOOP_PLAY] = sync_get_track(device, "loop#play");
            s_tracks[TRACK_CAN_X] = sync_get_track(device, "can#X");
            s_tracks[TRACK_CAN_Y] = sync_get_track(device, "can#Y");
            s_tracks[TRACK_FLOWER_STEM] = sync_get_track(device, "flower#stem");
            s_tracks[TRACK_FLOWER_OPENING] = sync_get_track(device, "flower#open");
            s_tracks[TRACK_HEART_X] = sync_get_track(device, "heart#X");
            s_tracks[TRACK_HEART_Y] = sync_get_track(device, "heart#Y");
        }

        virtual void start()
        {
            i = 0;
            for (int8_t f = 0; f < NUM_DROPS; f++)
            {
                icons[f][1] = 128;
            }
        }
int o = 0;
        virtual void update(bool buttonHeld)
        {
            if (_elapsed < 33)
                return;
//            display.startscrollleft(0, 0x0F);
            if (buttonHeld)
                resetSleepTimer();

            int loopDelta = sync_get_val_int(s_tracks[TRACK_LOOP], curtime_ms * rps / 1000.0);
            if (loopDelta > 0)
                curtime_ms = (loopDelta * 1000) / rps;
//         return row - loopDelta;
            float row_f = curtime_ms * rps / 1000.0f;
            // Serial.println(row_f);
            int8_t x = sync_get_val_int(s_tracks[TRACK_CAN_X], row_f);
            int8_t y = sync_get_val_int(s_tracks[TRACK_CAN_Y], row_f);

            _elapsed = 0;
            display.clearDisplay();
            display.drawBitmap(x, y, bmp_can, 19, 17, WHITE);

            uint8_t stem_length = (uint8_t) sync_get_val(s_tracks[TRACK_FLOWER_STEM], row_f);
            for (uint8_t s = 0; s < stem_length; s++)
            {
                display.drawPixel(30 + stem_offsets[s % 13], 128 - 5 - s, WHITE);
            }

            {
                int8_t flowerFrame = (int8_t) sync_get_val_int(s_tracks[TRACK_FLOWER_OPENING], row_f);
                if (flowerFrame > 8)
                    flowerFrame = 8;
                if (flowerFrame > 0)
                    display.drawBitmap(24, 50, epd_flower_allArray[flowerFrame], 16, 16, WHITE);
                display.drawBitmap(sync_get_val_int(s_tracks[TRACK_HEART_X], row_f),
                                   sync_get_val_int(s_tracks[TRACK_HEART_Y], row_f), bmp_heart, HEART_WIDTH,
                                   HEART_HEIGHT, WHITE);
            }
            // j++;

            display.drawFastHLine(5, 128 - 5, 64 - 10, WHITE);

            if (buttonHeld)
            {
                icons[i][0] = x + +18 + random(8);
                icons[i][1] = y + 15;
                i = ((i + 1) % NUM_DROPS);
            }

            bool playing = sync_get_val_int(s_tracks[TRACK_LOOP_PLAY], row_f) > 0;

            for (int8_t f = 0; f < NUM_DROPS; f++)
            {
                if (!playing && icons[f][1] == 123) { curtime_ms += 160; }
                if (icons[f][1] < 123)
                    icons[f][1] += 2;
                else
                    icons[f][1] = 128;
            }
            for (int8_t f = 0; f < NUM_DROPS; f++)
            {
                display.drawPixel(icons[f][0], icons[f][1], WHITE);
            }

            if (playing)
                curtime_ms += 160;

//            static const uint8_t PROGMEM scrollList3a[] = {
//                    SSD1306_SETDISPLAYOFFSET, 0X0a};
//            display.ssd1306_commandList(scrollList3a, 2);
            display.display();
        }

    };
}