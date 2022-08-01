#pragma once
#ifndef SIMULATOR
#include <Arduino.h>
#include <TFT_eSPI.h>
#endif
#include "global.h"
#include "elapsedMillis.h"
#include "device.h"
#include "utils.h"
#include "bitmap.h"
#include "rocket.h"
#include <cmath>

class Renderer
{
public:
    Renderer(TFT_eSprite* display) : display(display){}
  virtual void start() = 0;
  virtual void press(bool pressed)
  {
    if (pressed)
      this->start();
  }
  virtual void update(bool buttonHeld) {}
  virtual void stop() {}
  virtual void initTracks(sync_device* device) {

  }
  virtual ~Renderer() {}
  bool sleepTimerResetRequested()
  {
    bool val = _requestSleepTimerReset;
    _requestSleepTimerReset = false;
    return val;
  }

    virtual const char *getPrefix()
    {
        return nullptr;
    }

protected:
    TFT_eSprite* display;
  void resetSleepTimer()
  {
    _requestSleepTimerReset = true;
  }
   float getRowF(){return curtime_ms * rps / 1000.0f; }

private:
  bool _requestSleepTimerReset;
};

class TextRenderer : public Renderer
{
protected:
  bool _renderBitmap;

public:
  TextRenderer(TFT_eSprite* display,bool renderBitmap) : Renderer(display), _renderBitmap(renderBitmap)
  {
  }
  virtual void start()
  {
//    display->println(payload);
//    // Serial.println("Text bitmap=" + String(_renderBitmap ? "true" : "false"));
//    if (this->_renderBitmap)
//      display->drawBitmap(0, 128 - 48, epd_bitmap_et, 64, 47, WHITE);
//    display->display();
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
  TextRainRenderer(TFT_eSprite* display) : Renderer(display)  {}
  virtual void press(bool pressed)
  {
  }
  virtual void start()
  {
    // Initialize 'snowflake' positions
    for (int8_t f = 0; f < NUMFLAKES; f++)
    {
      icons[f][XPOS] = random(1 - HEART_WIDTH, display->width() - HEART_WIDTH);
      icons[f][YPOS] = display->height();
      icons[f][DELTAY] = random(2, 6);
    }
  }
  virtual void update(bool buttonHeld)
  {
    if (_elapsed < 33)
      return;
    _elapsed = 0;
    display->fillScreen(0);
    display->setCursor(0, 0);
    display->println(payload);

    // Draw each snowflake:
    for (int8_t f = 0; f < NUMFLAKES; f++)
    {
      display->drawBitmap(icons[f][XPOS], icons[f][YPOS], bmp_heart, HEART_WIDTH, HEART_HEIGHT, TFT_RED);
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
          icons[f][XPOS] = random(1, display->width() - HEART_WIDTH);
          icons[f][YPOS] = display->height();
          icons[f][DELTAY] = random(1, 6);
          break;
        }
      }
    }
  }
};
