#pragma once

#include <renderer.h>
#include <rocket.h>
#include "fonts/Pacifico_Regular20pt7b.h"

//const int8_t stem_offsets[] PROGMEM = {
//    0, 1, 2, 3, 3, 2, 1, 0, -1, -2, -3, -3, -2, -1};


// length 12
const uint8_t seq_short_long[] PROGMEM = {0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0};


namespace Rain {
    const unsigned char bmp_sun[] PROGMEM = {
            // 'sun', 32x31px
            0x00, 0x01, 0x80, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00,
            0x00, 0x0f, 0xf0, 0x00, 0x07, 0xc0, 0x03, 0xe0, 0x07, 0x0f, 0xf1, 0xe0, 0x07, 0x0f, 0xf1, 0xe0,
            0x06, 0x3f, 0xfc, 0x60, 0x06, 0x3f, 0xfc, 0x60, 0x00, 0xff, 0xfe, 0x00, 0x19, 0xff, 0xff, 0x80,
            0x19, 0xff, 0xff, 0x90, 0x39, 0xff, 0xff, 0x9c, 0x79, 0xff, 0xff, 0x9e, 0xf9, 0xff, 0xff, 0x9f,
            0x79, 0xff, 0xff, 0x9e, 0x39, 0xff, 0xff, 0x9c, 0x19, 0xff, 0xff, 0x90, 0x00, 0xff, 0xfe, 0x00,
            0x00, 0xff, 0xfe, 0x00, 0x06, 0x3f, 0xfc, 0x60, 0x06, 0x3f, 0xfc, 0x60, 0x07, 0x0f, 0xf1, 0xe0,
            0x07, 0xc0, 0x03, 0xe0, 0x07, 0xc0, 0x03, 0xe0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x0f, 0xf0, 0x00,
            0x00, 0x07, 0xc0, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00
    };
    // 'sprite_clouds0', 30x10px
    const unsigned char epd_bitmap_sprite_clouds0[] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00,
            0x07, 0x7f, 0x60, 0x00, 0x0f, 0xff, 0xf6, 0x00, 0x0f, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xc0,
            0x3f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00
    };
// 'sprite_clouds1', 30x10px
    const unsigned char epd_bitmap_sprite_clouds1[] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
            0x03, 0xc0, 0x00, 0x00, 0x1f, 0xe6, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x7f, 0xff, 0x80, 0x00,
            0x3f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
    };
// 'sprite_clouds2', 30x10px
    const unsigned char epd_bitmap_sprite_clouds2[] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
            0x01, 0xf0, 0x60, 0x00, 0x01, 0xfe, 0xf0, 0x00, 0x07, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0xfc, 0x00,
            0x1f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00
    };
// 'sprite_clouds3', 30x10px
    const unsigned char epd_bitmap_sprite_clouds3[] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x0f, 0xc0, 0x00,
            0x00, 0x1f, 0xe6, 0x00, 0x03, 0x1f, 0xff, 0x00, 0x07, 0xbf, 0xff, 0xc0, 0x1f, 0xff, 0xff, 0xe0,
            0x7f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00
    };
    const unsigned char *epd_bitmap_clouds[4] = {
            epd_bitmap_sprite_clouds0,
            epd_bitmap_sprite_clouds1,
            epd_bitmap_sprite_clouds2,
            epd_bitmap_sprite_clouds3,
    };
    // 'sprite_bolt0', 64x128px
    const unsigned char epd_bitmap_sprite_bolt0[] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x0c, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x01, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x04, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0xc0, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x30, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x01, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x40, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x40, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x04, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x40, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x03, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x40, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0xc0, 0x00, 0x00, 0x00,
            0x00, 0x03, 0x00, 0x01, 0x60, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x04, 0x00, 0x01, 0x18, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x01, 0x0c, 0x00, 0x00, 0x00,
            0x00, 0x04, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00,
            0x00, 0x04, 0x00, 0x01, 0x01, 0x80, 0x00, 0x00, 0x00, 0x04, 0x00, 0x01, 0x00, 0x80, 0x00, 0x00,
            0x00, 0x04, 0x00, 0x01, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x01, 0x00, 0x40, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x20, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x08, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x40, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0e, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x01, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x04, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
// 'sprite_bolt1', 64x128px
    const unsigned char epd_bitmap_sprite_bolt1[] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x10, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x98, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x04, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x01, 0xf0, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 2080)
    const int epd_bitmap_bolts_LEN = 2;
    const unsigned char *epd_bitmap_bolts[2] = {
            epd_bitmap_sprite_bolt0,
            epd_bitmap_sprite_bolt1
    };

    // 'sprite_tree0', 41x66px
    const unsigned char epd_bitmap_sprite_tree0 [] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x06, 0xf0, 0x00,
            0x00, 0x00, 0x00, 0x06, 0x30, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x38, 0x00, 0x00, 0x00, 0x00, 0x10,
            0x1c, 0x00, 0x00, 0x00, 0x00, 0x20, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x40, 0xae, 0x00, 0x00, 0x00,
            0x00, 0x41, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x47, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xaf, 0xff, 0xe0,
            0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x36,
            0x2f, 0x80, 0x00, 0x00, 0x00, 0x40, 0x2f, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x01, 0xc0, 0x00, 0x00,
            0x00, 0x82, 0x50, 0xe0, 0x00, 0x00, 0x00, 0xcf, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0,
            0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0xfe,
            0xff, 0xe0, 0x00, 0x00, 0x01, 0x22, 0xbf, 0xe0, 0x00, 0x00, 0x01, 0x00, 0x1f, 0xe0, 0x00, 0x00,
            0x02, 0x00, 0x5f, 0x70, 0x00, 0x00, 0x02, 0x01, 0x02, 0xf8, 0x00, 0x00, 0x03, 0x7f, 0xed, 0xf0,
            0x00, 0x00, 0x03, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x03, 0xff,
            0xff, 0xf0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x0b, 0x55, 0xff, 0xf8, 0x00, 0x00,
            0x09, 0x02, 0xaf, 0xfe, 0x00, 0x00, 0x10, 0x00, 0xaf, 0xfe, 0x00, 0x00, 0x10, 0x20, 0x00, 0x2e,
            0x00, 0x00, 0x1a, 0xa1, 0x45, 0x4e, 0x00, 0x00, 0x07, 0xf7, 0xd7, 0xfc, 0x00, 0x00, 0x07, 0xff,
            0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xfe, 0x00, 0x00,
            0x3e, 0x9f, 0xff, 0xfe, 0x00, 0x00, 0x6a, 0x17, 0x5f, 0xfe, 0x00, 0x00, 0x40, 0x00, 0x17, 0xfe,
            0x00, 0x00, 0x40, 0x00, 0xa2, 0x24, 0x00, 0x00, 0x45, 0xaa, 0xb3, 0x6e, 0x00, 0x00, 0x7f, 0xff,
            0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x00,
            0x0f, 0xff, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x03, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00,
            0x00, 0x00, 0x00, 0x02, 0x70, 0x00, 0x00, 0x00, 0x00, 0x02, 0x70, 0x00, 0x00, 0x00, 0x00, 0x02,
            0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00,
            0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00,
            0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x02,
            0xf0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00,
            0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
// 'sprite_tree1', 41x66px
    const unsigned char epd_bitmap_sprite_tree1 [] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
            0x00, 0x00, 0x00, 0x00, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce, 0x00, 0x00, 0x00, 0x00, 0x07,
            0x66, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x08, 0x27, 0x00, 0x00, 0x00,
            0x00, 0x10, 0x23, 0x80, 0x00, 0x00, 0x00, 0x10, 0x7b, 0x80, 0x00, 0x00, 0x00, 0x11, 0xf3, 0xe0,
            0x00, 0x00, 0x00, 0x2b, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x1f,
            0xdf, 0xf8, 0x00, 0x00, 0x00, 0x0d, 0x8f, 0xf0, 0x00, 0x00, 0x00, 0x10, 0x0b, 0xe0, 0x00, 0x00,
            0x00, 0x40, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x41, 0x20, 0xe0, 0x00, 0x00, 0x00, 0x67, 0xe8, 0x70,
            0x00, 0x00, 0x00, 0x7f, 0xff, 0x70, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x7f,
            0xff, 0xe0, 0x00, 0x00, 0x00, 0xff, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x91, 0x5f, 0xf0, 0x00, 0x00,
            0x01, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x01, 0x00, 0x2f, 0xf0, 0x00, 0x00, 0x03, 0x01, 0x1f, 0xb8,
            0x00, 0x00, 0x03, 0xff, 0xe2, 0xf8, 0x00, 0x00, 0x03, 0xff, 0xed, 0xf0, 0x00, 0x00, 0x03, 0xff,
            0xff, 0xf8, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x0b, 0xff, 0xff, 0xf0, 0x00, 0x00,
            0x09, 0x55, 0xff, 0xf8, 0x00, 0x00, 0x10, 0x02, 0xbf, 0xf8, 0x00, 0x00, 0x10, 0x00, 0xaf, 0xf8,
            0x00, 0x00, 0x1a, 0x20, 0x0f, 0xfe, 0x00, 0x00, 0x0f, 0x61, 0x40, 0x2e, 0x00, 0x00, 0x0f, 0xef,
            0xaa, 0x9f, 0x00, 0x00, 0x1f, 0xff, 0xf7, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xfc, 0x00, 0x00,
            0x3e, 0x9f, 0xff, 0xfc, 0x00, 0x00, 0x6a, 0x17, 0x5f, 0xff, 0x80, 0x00, 0x40, 0x00, 0x17, 0xff,
            0x80, 0x00, 0x40, 0x00, 0xa2, 0x25, 0x80, 0x00, 0x45, 0xaa, 0xb3, 0x6f, 0xc0, 0x00, 0x7f, 0xff,
            0xff, 0xff, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x00,
            0x0f, 0xff, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x01, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x01, 0x58, 0x00,
            0x00, 0x00, 0x00, 0x01, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01,
            0x78, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00,
            0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00,
            0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x02,
            0xf0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00,
            0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
// 'sprite_tree2', 41x66px
    const unsigned char epd_bitmap_sprite_tree2 [] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x06, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x70, 0x00, 0x00, 0x00, 0x00, 0x46, 0x60, 0x00, 0x00,
            0x00, 0x00, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x01, 0x02, 0x70, 0x00, 0x00, 0x00, 0x01, 0x02, 0x38,
            0x00, 0x00, 0x00, 0x01, 0x1f, 0xb8, 0x00, 0x00, 0x00, 0x02, 0xbf, 0x3e, 0x00, 0x00, 0x00, 0x03,
            0xff, 0xfe, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xdd, 0xff, 0x80, 0x00,
            0x00, 0x03, 0x00, 0xff, 0x80, 0x00, 0x00, 0x08, 0x01, 0x7c, 0x00, 0x00, 0x00, 0x08, 0x20, 0xfc,
            0x00, 0x00, 0x00, 0x0c, 0xfc, 0x1c, 0x00, 0x00, 0x00, 0x0f, 0xfd, 0x0e, 0x00, 0x00, 0x00, 0x0f,
            0xff, 0xee, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x1f, 0xef, 0xfe, 0x00, 0x00,
            0x00, 0x12, 0x2f, 0xfc, 0x00, 0x00, 0x00, 0x20, 0x0b, 0xfe, 0x00, 0x00, 0x00, 0xc0, 0x03, 0xfe,
            0x00, 0x00, 0x00, 0xc0, 0x4b, 0xfc, 0x00, 0x00, 0x00, 0xff, 0xf7, 0xec, 0x00, 0x00, 0x00, 0xff,
            0xf8, 0xbe, 0x00, 0x00, 0x01, 0xff, 0xfb, 0x7e, 0x00, 0x00, 0x02, 0xff, 0xff, 0xfc, 0x00, 0x00,
            0x02, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x04, 0x15, 0x7f, 0xfe, 0x00, 0x00, 0x04, 0x00, 0xaf, 0xfc,
            0x00, 0x00, 0x06, 0x80, 0x2f, 0xfe, 0x00, 0x00, 0x07, 0x90, 0x0b, 0xfe, 0x00, 0x00, 0x07, 0xf0,
            0xa7, 0xfc, 0x00, 0x00, 0x0f, 0xf7, 0xd0, 0x17, 0x00, 0x00, 0x1f, 0xff, 0xf5, 0x4f, 0x00, 0x00,
            0x3e, 0x9f, 0xfb, 0xff, 0x80, 0x00, 0x6a, 0x17, 0x5f, 0xff, 0x00, 0x00, 0x40, 0x00, 0x17, 0xff,
            0x80, 0x00, 0x40, 0x00, 0xa2, 0x25, 0x80, 0x00, 0x45, 0xaa, 0xb3, 0x6f, 0xc0, 0x00, 0x7f, 0xff,
            0xff, 0xff, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x00,
            0x0f, 0xff, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x01, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x01, 0x58, 0x00,
            0x00, 0x00, 0x00, 0x01, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01,
            0x78, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00,
            0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00,
            0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x02,
            0xf0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00,
            0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
// 'sprite_tree3', 41x66px
    const unsigned char epd_bitmap_sprite_tree3 [] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x9c, 0x00, 0x00,
            0x00, 0x00, 0x11, 0x98, 0x00, 0x00, 0x00, 0x00, 0x20, 0x38, 0x00, 0x00, 0x00, 0x00, 0x40, 0x9c,
            0x00, 0x00, 0x00, 0x00, 0x40, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x47, 0xee, 0x00, 0x00, 0x00, 0x00,
            0xaf, 0xcf, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xc0, 0x00,
            0x00, 0x00, 0x6e, 0xff, 0xc0, 0x00, 0x00, 0x01, 0x80, 0x7f, 0xc0, 0x00, 0x00, 0x04, 0x00, 0xbe,
            0x00, 0x00, 0x00, 0x04, 0x10, 0x7e, 0x00, 0x00, 0x00, 0x06, 0x7e, 0x0e, 0x00, 0x00, 0x00, 0x07,
            0xfe, 0x87, 0x00, 0x00, 0x00, 0x07, 0xff, 0xf7, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x00, 0x00,
            0x00, 0x0f, 0xf7, 0xff, 0x00, 0x00, 0x00, 0x11, 0x17, 0xfe, 0x00, 0x00, 0x00, 0x60, 0x05, 0xff,
            0x00, 0x00, 0x00, 0x60, 0x01, 0xff, 0x00, 0x00, 0x00, 0x78, 0x25, 0xfe, 0x00, 0x00, 0x00, 0x7f,
            0xfb, 0xf6, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x5f, 0x00, 0x00, 0x01, 0x7f, 0xfd, 0xbf, 0x00, 0x00,
            0x01, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x02, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x02, 0x02, 0xbf, 0xff,
            0x00, 0x00, 0x03, 0x40, 0x57, 0xfe, 0x00, 0x00, 0x03, 0xc8, 0x17, 0xff, 0x00, 0x00, 0x03, 0xf8,
            0x05, 0xff, 0x00, 0x00, 0x0f, 0xf0, 0xa7, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xd0, 0x17, 0x00, 0x00,
            0x3e, 0x9f, 0xf5, 0x4f, 0x00, 0x00, 0x6a, 0x17, 0xfb, 0xff, 0x80, 0x00, 0x40, 0x07, 0x5f, 0xff,
            0x00, 0x00, 0x40, 0x00, 0x17, 0xff, 0x80, 0x00, 0x45, 0xa8, 0xa2, 0x25, 0x80, 0x00, 0x7f, 0xfa,
            0xb3, 0x6f, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x00,
            0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x01, 0x58, 0x00,
            0x00, 0x00, 0x00, 0x01, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01,
            0x78, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00,
            0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb0, 0x00,
            0x00, 0x00, 0x00, 0x02, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x02,
            0xf0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00,
            0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // 'stork', 30x20px
    const unsigned char epd_bitmap_stork [] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x00, 0x00,
            0x00, 0xf6, 0x00, 0x00, 0x01, 0x7f, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0xfb, 0x80, 0x00,
            0x01, 0xfb, 0x80, 0x00, 0x00, 0xfb, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x7b, 0x00, 0x00,
            0x00, 0x1b, 0x00, 0x00, 0x00, 0x19, 0x30, 0x00, 0x00, 0xf8, 0x48, 0x00, 0x10, 0xf8, 0xf7, 0x80,
            0x7f, 0xff, 0x83, 0x00, 0x08, 0x1e, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1664)
    const int epd_tree_LEN = 4;
    const unsigned char* epd_tree_allArray[4] = {
            epd_bitmap_sprite_tree0,
            epd_bitmap_sprite_tree1,
            epd_bitmap_sprite_tree2,
            epd_bitmap_sprite_tree3
    };

    const char *Labels[] = {
            "Tout", "est", "mieux", "avec", "toi"
    };
    const size_t LabelsSize = sizeof_array(Labels);


    enum class RainTracks : uint8_t {
        Track_loop = 0,
        Track_loop_play = 1,
        Track_sun_x = 2,
        Track_sun_y = 3,
        Track_rain = 4,
        Track_clouds = 5,
        Track_TextLabel = 6,
    };
    const uint8_t NUM_DROPS = 80;

    struct Drop {
        uint8_t x, y;
        bool alive;
    };

    class RainRenderer
            : public Renderer {

    protected:
        uint8_t i;
        Drop icons[NUM_DROPS];
        elapsedMillis _elapsed;
        elapsedMillis _totalElapsed;
        Timer _boltTimer;
        Timer _rainTimer;
        const struct sync_track *s_tracks[7];
    public:
        virtual void press(bool pressed) {}

        const char *getPrefix() override
        {
            return "rain";
        }

        virtual void initTracks(sync_device *device) {
            s_tracks[(int) RainTracks::Track_loop] = sync_get_track(device, "loop#goto");
            s_tracks[(int) RainTracks::Track_loop_play] = sync_get_track(device, "loop#play");
            s_tracks[(int) RainTracks::Track_sun_x] = sync_get_track(device, "sun#X");
            s_tracks[(int) RainTracks::Track_sun_y] = sync_get_track(device, "sun#Y");
            s_tracks[(int) RainTracks::Track_rain] = sync_get_track(device, "rain#intensity");
            s_tracks[(int) RainTracks::Track_clouds] = sync_get_track(device, "clouds#x");
            s_tracks[(int) RainTracks::Track_TextLabel] = sync_get_track(device, "text#label");
        }

        virtual void start() {
            i = 0;
            for (int8_t f = 0; f < NUM_DROPS; f++) {
                icons[f].alive = false;
            }
        }

        const sync_track *track(RainTracks t) { return s_tracks[(uint8_t) t]; }

        int get_int(RainTracks t, float row_f) { return sync_get_val_int(s_tracks[(uint8_t) t], row_f); }

        virtual void update(bool buttonHeld) {
            if (_elapsed < 33)
                return;
            _elapsed = 0;
            long totalElapsed = _totalElapsed;
            float row_f = curtime_ms * rps / 1000.0f;
            int play = get_int(RainTracks::Track_loop_play, row_f);
            int clouds = get_int(RainTracks::Track_clouds, row_f);
            bool ignoreButton = get_int(RainTracks::Track_loop, row_f) != 0;
            if (buttonHeld)
                resetSleepTimer();
            if(!ignoreButton) {
                audio_is_playing = buttonHeld;
                if (buttonHeld) {
                    if (play)
                        curtime_ms += 33;
                } else if (curtime_ms > 0) {
                    curtime_ms -= 33;
                    curtime_ms = max(0, min(curtime_ms, 3000));
                }
            }
            display.clearDisplay();

            int8_t x = sync_get_val_int(track(RainTracks::Track_sun_x), row_f);
            int8_t y = sync_get_val_int(track(RainTracks::Track_sun_y), row_f);
            display.drawBitmap(x, y, bmp_sun, 32, 31, WHITE);
            const uint8_t groundLevel = 122;
            // ground
            display.drawFastHLine(0, groundLevel + 1, 64, WHITE);

            int8_t rainIntensity = sync_get_val_int(track(RainTracks::Track_rain), row_f);

            // TREE
            int treeframe = 0;

            // 4
            // 0 1 2 3 2 1 0
            // 0 1 2 3 4 5 6
            //         _ _ _
            if (rainIntensity > 60) {
                auto dbl = (epd_tree_LEN)*2-1; // 7
                treeframe=(_totalElapsed / 200)% (dbl * 3);
                if(treeframe > dbl)
                    treeframe = 0;
                else if(treeframe >= epd_tree_LEN)
                    treeframe = dbl - treeframe;
            }
            display.drawBitmap(-4, groundLevel - 65, epd_tree_allArray[treeframe], 41, 66, WHITE);

            // STORK
            display.drawBitmap((_totalElapsed / 60) % 100 - 20, 50 - rainIntensity * 2, epd_bitmap_stork, 30, 20, INVERSE);


            // RAIN
            if (rainIntensity > NUM_DROPS)
                rainIntensity = NUM_DROPS;
            _rainTimer.setDuration(0);
            _rainTimer.setCooldown(100 * (1.0f  - rainIntensity/(float)NUM_DROPS));
            _rainTimer.update();
            if(_rainTimer.endedCooldown())
            for (int8_t f = 0; f < rainIntensity; f++) {
                if (!icons[f].alive) {
                    icons[f] = {
                            (uint8_t) random(64),
                            14,
                            true
                    };
                    break;
                }
            }
            for (int8_t f = 0; f < NUM_DROPS; f++) {
                if (icons[f].alive) {
                    icons[f].y += 2;
                    icons[f].x += 1;
                    if (icons[f].x > display.width())
                        icons[f].x = 0;
                    if (icons[f].y > groundLevel)
                        icons[f].alive = false;
                    else {

                        display.drawPixel(icons[f].x, icons[f].y, WHITE);
                    }
                }
            }

            // CLOUDS
            for (int8_t c = 0; c < clouds; ++c) {
                // two lines
                int16_t y = 3 + (c % 3) * 5;
                // speed 1/2/3
                int16_t speed = (c % 3) + 1;
                // add horiz movement
                int16_t x = (c * 39 + speed * (totalElapsed / 600)) % (64 + 20) - 20 + fmax(0, 100 - rainIntensity);


                display.drawBitmap(x - 1, y - 1, epd_bitmap_clouds[c % 4], 30, 10, BLACK);
                display.drawBitmap(x, y, epd_bitmap_clouds[c % 4], 30, 10, WHITE);
            }

            if (_boltTimer.endedCooldown()) {
                _boltTimer.setDuration(random(3000, 5000));
                _boltTimer.setCooldown(random(300, 600));
                display.invertDisplay(false);
//                Serial.println("ended");
            }
            _boltTimer.update();
            if (rainIntensity > 60) {
                float bolt_progress = _boltTimer.cooldownProgress();
//            Serial.println(bolt_progress);
                if (bolt_progress > 0) {
                    uint8_t bolt_on = seq(seq_short_long, 12, bolt_progress, _boltTimer.getCooldown(), false);
//                    uint8_t bolt_on = seq_short_long[((/*0-500*/_boltTimer - 1000) * 12 / 500) % 12];
                    if (bolt_on)
                        display.drawBitmap(((_boltTimer.getCycleCount() * 11) % 15) - 7, 0,
                                           epd_bitmap_bolts[_boltTimer.getCycleCount() % epd_bitmap_bolts_LEN], 64, 128,
                                           WHITE);
                    display.invertDisplay(bolt_on);
                }
            }
            if (_boltTimer.endedCooldown()) {
                _boltTimer.setDuration(random(1000, 5000));
                _boltTimer.setCooldown(random(300, 600));
                display.invertDisplay(false);
            }

            int label = get_int(RainTracks::Track_TextLabel, row_f);
            if (label >= 0) {
                display.fillRect(0, 80, 64, 30, WHITE);
                display.setCursor(4, 100);
                display.setTextWrap(false);
                display.setFont(&Pacifico_Regular12pt7b);
                display.setTextColor(INVERSE);
                display.println(Labels[label % LabelsSize]);
            }
            display.setFont(nullptr);
            display.setTextWrap(true);
//            display.ssd1306_command(SSD1306_SETSTARTLINE | (uint8_t)((offset++) % 64));

            display.display();
        }
        uint8_t offset;
    };
}