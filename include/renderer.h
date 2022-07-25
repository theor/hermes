#pragma once

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "global.h"
#include "elapsedMillis.h"

class Renderer
{
public:
  virtual void start() = 0;
  virtual void press(bool pressed)
  {
    if (pressed)
      this->start();
  }
  virtual void update(bool buttonHeld) {}
  virtual void stop() {}
  virtual ~Renderer() {}
  bool sleepTimerResetRequested()
  {
    bool val = _requestSleepTimerReset;
    _requestSleepTimerReset = false;
    return val;
  }

protected:
  void resetSleepTimer()
  {
    _requestSleepTimerReset = true;
  }

private:
  bool _requestSleepTimerReset;
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
  virtual void press(bool pressed)
  {
    resetSleepTimer();
  }
  virtual void start()
  {
    // Initialize 'snowflake' positions
    for (int8_t f = 0; f < NUMFLAKES; f++)
    {
      icons[f][XPOS] = random(1 - HEART_WIDTH, display.width() - HEART_WIDTH);
      icons[f][YPOS] = display.height();
      icons[f][DELTAY] = random(2, 6);
    }
  }
  virtual void update(bool buttonHeld)
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
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bmp_heart, HEART_WIDTH, HEART_HEIGHT, WHITE);
    }
    for (int8_t f = 0; f < NUMFLAKES; f++)
    {

      if (icons[f][YPOS] > -HEART_HEIGHT)
      {
        icons[f][YPOS] -= icons[f][DELTAY];
        icons[f][XPOS] += random(-1, 1);
      }
      // If snowflake is off the bottom of the screen...
      // if (icons[f][YPOS] >= 128) {
      //   // Reinitialize to a random position, just off the top
      //   icons[f][XPOS]   = random(1 - HEART_WIDTH, 64);
      //   icons[f][YPOS]   = -HEART_HEIGHT;
      //   icons[f][DELTAY] = random(1, 6);
      // }
    }

    if (buttonHeld)
    {
      for (int8_t f = 0; f < NUMFLAKES; f++)
      {
        if (icons[f][YPOS] < 0)
        {
          //   // Reinitialize to a random position, just off the top
          icons[f][XPOS] = random(1, display.width() - HEART_WIDTH);
          icons[f][YPOS] = display.height();
          icons[f][DELTAY] = random(1, 6);
          break;
        }
      }
    }

    display.display();
  }
};
