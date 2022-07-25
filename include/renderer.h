#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "global.h"
#include "elapsedMillis.h"

class Renderer
{
public:
  virtual void start() = 0;
  virtual void press(bool pressed) { if(pressed) this->start(); }
  virtual void update() {}
  virtual void stop() {}
  virtual ~Renderer() {}
};

class TextRenderer : public Renderer
{
protected:
  bool _renderBitmap;

public:
  TextRenderer(bool renderBitmap) : _renderBitmap(renderBitmap)
  {
    Serial.print("CTOR " + String(renderBitmap));
    Serial.println(_renderBitmap);
  }
  virtual void start()
  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(payload);
    // Serial.println("Text bitmap=" + String(_renderBitmap ? "true" : "false"));
    if (this->_renderBitmap)
      display.drawBitmap(0, 128 - 48, epd_bitmap_et, 64, 47, WHITE);
    display.display();
  }
};

#define NUMFLAKES 10
#define LOGO_HEIGHT 10
#define LOGO_WIDTH 11
static const unsigned char PROGMEM logo_bmp[] =
    {0x7b, 0xc0, 0xff, 0xe0, 0xff, 0xe0, 0xfe, 0x60, 0xff, 0xe0, 0x7f, 0xc0, 0x3f, 0x80, 0x1f, 0x00,
     0x0e, 0x00, 0x04, 0x00};
#define XPOS 0 // Indexes into the 'icons' array in function below
#define YPOS 1
#define DELTAY 2
class TextRainRenderer : public Renderer
{
protected:
  int16_t icons[NUMFLAKES][3];
  elapsedMillis _elapsed;

public:
  TextRainRenderer() {}
  virtual void start()
  {
    // Initialize 'snowflake' positions
    for (int8_t f = 0; f < NUMFLAKES; f++)
    {
      icons[f][XPOS] = random(1 - LOGO_WIDTH, display.width());
      icons[f][YPOS] = -LOGO_HEIGHT;
      icons[f][DELTAY] = random(2, 6);
    }
  }
  virtual void update()
  {
    if (_elapsed < 33)
      return;
    _elapsed = 0;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(payload);

    // Draw each snowflake:
    for (int8_t f = 0; f < NUMFLAKES; f++)
    {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, WHITE);
    }
    for (int8_t f = 0; f < NUMFLAKES; f++)
    {

      if (icons[f][YPOS] < 128)
        icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      // if (icons[f][YPOS] >= 128) {
      //   // Reinitialize to a random position, just off the top
      //   icons[f][XPOS]   = random(1 - LOGO_WIDTH, 64);
      //   icons[f][YPOS]   = -LOGO_HEIGHT;
      //   icons[f][DELTAY] = random(1, 6);
      // }
    }
    display.display();
  }
};
