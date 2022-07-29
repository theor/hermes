#pragma once

#ifndef SIMULATOR
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class AsyncWebServer;

extern AsyncWebServer server;
class Renderer;

extern String payload;
extern Adafruit_SSD1306 display;
//extern AsyncWebServer server;
extern Renderer *renderer;
#else
#include <string>
extern std::string payload;

#endif
extern bool uploadMode;
extern bool debugMode;

#define LED_PIN 2                // ESP32 Pin to which onboard LED is connected

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

#define Threshold 40 /* Greater the value, more the sensitivity */

#define SENTINEL_VALUE ((uint8_t)42)
#define SENTINEL_OFFSET 0
#define MSG_OFFSET 10
#define MODE_OFFSET 1
#define DEBUGMODE_OFFSET 2


enum class RenderMode : uint8_t
{
  Text = 0,
  TextAndBitmap = 1,
  TextRain = 2,
  Plant = 3,
  Rain = 4,
  END = 5,
};
