/*
  Rui Santos
  Complete project details
   - Arduino IDE: https://RandomNerdTutorials.com/esp32-ota-over-the-air-arduino/
   - VS Code: https://RandomNerdTutorials.com/esp32-ota-over-the-air-vs-code/

  This sketch shows a Basic example from the AsyncElegantOTA library: ESP32_Async_Demo
  https://github.com/ayushsharma82/AsyncElegantOTA
*/

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "WifiConfig.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HTTPClient.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define Threshold 40 /* Greater the value, more the sensitivity */

// variabls for blinking an LED with Millis
const int led = 2;                // ESP32 Pin to which onboard LED is connected
unsigned long previousMillis = 0; // will store last time LED was updated
const long interval = 300;        // interval at which to blink (milliseconds)
int ledState = LOW;               // ledState used to set the LED

AsyncWebServer server(80);

class elapsedMillis
{
private:
  unsigned long ms;

public:
  elapsedMillis(void) { ms = millis(); }
  elapsedMillis(unsigned long val) { ms = millis() - val; }
  elapsedMillis(const elapsedMillis &orig) { ms = orig.ms; }
  operator unsigned long() const { return millis() - ms; }
  elapsedMillis &operator=(const elapsedMillis &rhs)
  {
    ms = rhs.ms;
    return *this;
  }
  elapsedMillis &operator=(unsigned long val)
  {
    ms = millis() - val;
    return *this;
  }
  elapsedMillis &operator-=(unsigned long val)
  {
    ms += val;
    return *this;
  }
  elapsedMillis &operator+=(unsigned long val)
  {
    ms -= val;
    return *this;
  }
  elapsedMillis operator-(int val) const
  {
    elapsedMillis r(*this);
    r.ms += val;
    return r;
  }
  elapsedMillis operator-(unsigned int val) const
  {
    elapsedMillis r(*this);
    r.ms += val;
    return r;
  }
  elapsedMillis operator-(long val) const
  {
    elapsedMillis r(*this);
    r.ms += val;
    return r;
  }
  elapsedMillis operator-(unsigned long val) const
  {
    elapsedMillis r(*this);
    r.ms += val;
    return r;
  }
  elapsedMillis operator+(int val) const
  {
    elapsedMillis r(*this);
    r.ms -= val;
    return r;
  }
  elapsedMillis operator+(unsigned int val) const
  {
    elapsedMillis r(*this);
    r.ms -= val;
    return r;
  }
  elapsedMillis operator+(long val) const
  {
    elapsedMillis r(*this);
    r.ms -= val;
    return r;
  }
  elapsedMillis operator+(unsigned long val) const
  {
    elapsedMillis r(*this);
    r.ms -= val;
    return r;
  }
};
elapsedMillis sleepTimer;

void pullMessage()
{
  HTTPClient http;
  http.begin("https://theor.github.io/hermes/content.txt");
  int httpResponseCode = http.GET();
  display.ssd1306_command(SSD1306_DISPLAYON);
  display.setFont(nullptr);
  display.setTextColor(WHITE, BLACK);
  display.clearDisplay();
  display.setCursor(0, 0);
  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);

    delay(100);
    display.println("ASD ASD");
    display.display();
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}
void callback()
{
  sleepTimer = 0;
  // placeholder callback function
}

void initDisplay()
{

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.

  // Clear the buffer
  display.setRotation(1);
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
}

void setup(void)
{
  pinMode(led, OUTPUT);
  Serial.begin(115200);

  initDisplay();

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pullMessage();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hi! I am ESP32."); });

  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");

  touchAttachInterrupt(T3, callback, Threshold);

  // Configure Touchpad as wakeup source
  esp_sleep_enable_touchpad_wakeup();
}

elapsedMillis touchTimer;
bool uploadMode = false;

void loop(void)
{
  // loop to blink without delay
  unsigned long currentMillis = millis();

if(uploadMode){
  display.setCursor(0, 0);
  display.setTextColor(WHITE, BLACK);
  display.clearDisplay();
  display.println(F("Upload"));
  display.display();
}

  if (uploadMode && currentMillis - previousMillis >= interval)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    ledState = not(ledState);
    // set the LED with the ledState of the variable:
    digitalWrite(led, ledState);
  }

  if (!uploadMode && sleepTimer > 10000)
  {
    // Go to sleep now
    Serial.println("Going to sleep now");
    display.clearDisplay();
    display.ssd1306_command(SSD1306_DISPLAYOFF);
    esp_deep_sleep_start();
  }

  int touch = touchRead(T3);
  // Serial.println(touch);
  if (touch > Threshold)
  {
    touchTimer = 0;
  }
  else
  {
    if (touchTimer > 2000)
    {
      uploadMode = !uploadMode;
      touchTimer = 0;
      Serial.print("uploadMode: ");
      Serial.println(uploadMode ? "true" : "false");
    }
  }
}

// /*********
//   Complete project details at https://randomnerdtutorials.com

//   This is an example for our Monochrome OLEDs based on SSD1306 drivers. Pick one up today in the adafruit shop! ------> http://www.adafruit.com/category/63_98
//   This example is for a 128x32 pixel display using I2C to communicate 3 pins are required to interface (two I2C and one reset).
//   Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!
//   Written by Limor Fried/Ladyada for Adafruit Industries, with contributions from the open source community. BSD license, check license.txt for more information All text above, and the splash screen below must be included in any redistribution.
// *********/

// #include <WiFi.h>
// #include <WifiConfig.h>

// #define NUMFLAKES 10 // Number of snowflakes in the animation example

// #define LOGO_HEIGHT 16
// #define LOGO_WIDTH 16
// static const unsigned char PROGMEM logo_bmp[] =
//     {B00000000, B11000000,
//      B00000001, B11000000,
//      B00000001, B11000000,
//      B00000011, B11100000,
//      B11110011, B11100000,
//      B11111110, B11111000,
//      B01111110, B11111111,
//      B00110011, B10011111,
//      B00011111, B11111100,
//      B00001101, B01110000,
//      B00011011, B10100000,
//      B00111111, B11100000,
//      B00111111, B11110000,
//      B01111100, B11110000,
//      B01110000, B01110000,
//      B00000000, B00110000};

// void initWiFi()
// {
//   Serial.println("Connecting to WiFi ..");
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(SSID, PASSWORD);
//   uint8_t i = 0;
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     if (i++ % 2 == 0)
//       Serial.print('.');
//     else
//       Serial.print(" .");
//     // Serial.Serial();
//     delay(500);
//   }
//   // Serial.clearSerial();
//   Serial.println(WiFi.localIP());
//   display.clearDisplay();

//   display.setTextSize(1);      // Normal 1:1 pixel scale
//   display.setTextColor(WHITE); // Draw white text
//   display.setCursor(0, 0);     // Start at top-left corner
//   display.println(WiFi.localIP().toString());
//   display.display();
// }

// void setup()
// {
//   Serial.begin(115200);
//   int i = 0;
//   while (!Serial && i++ < 1000)
//     ;

// }

// void loop()
// {
//   if(!digitalRead(0))
//     pullMessage();
// }
