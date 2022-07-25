/*
  Rui Santos
  Complete project details
   - Arduino IDE: https://RandomNerdTutorials.com/esp32-ota-over-the-air-arduino/
   - VS Code: https://RandomNerdTutorials.com/esp32-ota-over-the-air-vs-code/

  This sketch shows a Basic example from the AsyncElegantOTA library: ESP32_Async_Demo
  https://github.com/ayushsharma82/AsyncElegantOTA
*/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <Arduino.h>
#include <Wire.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "WifiConfig.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Bounce2.h>
#include <EEPROM.h>
#pragma GCC diagnostic pop

#include "bitmap.h"
#include "global.h"
#include "renderer.h"
#include "TouchButton.h"
#include "elapsedMillis.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define Threshold 40 /* Greater the value, more the sensitivity */
TouchButton touchButton(Threshold);

// variabls for blinking an LED with Millis
const int led = 2;                // ESP32 Pin to which onboard LED is connected
unsigned long previousMillis = 0; // will store last time LED was updated
const long interval = 300;        // interval at which to blink (milliseconds)
int ledState = LOW;               // ledState used to set the LED

bool uploadMode = false;
bool latched = false;
bool running = false;

enum class RenderMode : uint8_t
{
  Text = 0,
  TextAndBitmap = 1,
  TextRain = 2,
  END = 3,
};

RenderMode mode = RenderMode::TextAndBitmap;

AsyncWebServer server(80);

String payload;
elapsedMillis sleepTimer;

const uint8_t SENTINEL_VALUE = 42;
#define SENTINEL_OFFSET 0
#define MSG_OFFSET 10
#define MODE_OFFSET 1

const char *PARAM_INPUT_1 = "input1";
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/set">
    Message: <textarea type="text" name="input1"></textarea>
    <input type="submit" value="Submit">
  </form>
  <form action="/setMode">
    Mode: <select name="input1">
    <option value="0">Text</option>
    <option value="1">Text and bitmap</option>
    <option value="2">Text and rain</option>
    </select>
    <input type="submit" value="Submit">
  </form>
  <a href="/run">Leave upload mode</a>
</body></html>)rawliteral";


Renderer *renderer;
void setRenderer(RenderMode newMode)
{
  mode = newMode;
  if (renderer)
  {
    renderer->stop();
    delete renderer;
    renderer = nullptr;
  }
  Serial.print("CURRENT MODE");
  Serial.println((int)mode);
  switch (mode)
  {
  case RenderMode::TextRain:
    renderer = new TextRainRenderer();
    break;
  case RenderMode::TextAndBitmap:
    renderer = new TextRenderer(true);
    break;
  default:
    renderer = new TextRenderer(false);
    break;
  }
  renderer->start();
}

void pullMessage()
{
  display.ssd1306_command(SSD1306_DISPLAYON);
  display.setFont(nullptr);
  display.setTextColor(WHITE, BLACK);

  Serial.print("eeprom size:");
  Serial.println(EEPROM.length());
  if (EEPROM.readByte(SENTINEL_OFFSET) != SENTINEL_VALUE)
    payload = F("No data");
  else
  {
    payload = EEPROM.readString(MSG_OFFSET);
    mode = (RenderMode)EEPROM.readByte(MODE_OFFSET);
  }
  if (payload.length() == 0)
    payload = F("No message");
  Serial.println(payload + " " + String((int)mode));

  setRenderer(mode);
}
void callback()
{
  sleepTimer = 0;
  // Serial.println("touched");
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

bool connected = false;
void setup(void)
{
  running = false;
  connected = false;
  pinMode(led, OUTPUT);
  EEPROM.begin(512);

  touchButton.attach(T3);
  touchButton.interval(50); // interval in ms
  touchButton.reset();

  Serial.begin(115200);

  initDisplay();
  pullMessage();

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html); });
  server.on("/run", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
    uploadMode = false;
        digitalWrite(led, LOW);
        pullMessage();
        request->redirect(F("/")); });
  server.on("/setMode", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if (request->hasParam(PARAM_INPUT_1))
    {
      int i = request->getParam(PARAM_INPUT_1)->value().toInt();
      if (i >= 0 && i < (int)RenderMode::END)
      {
        RenderMode newMode = static_cast<RenderMode>((uint8_t)i);

        EEPROM.writeByte(MODE_OFFSET, (uint8_t)newMode);
        EEPROM.commit();
        setRenderer(newMode);
        request->send(200, "text/html", "Set mode to " + String((uint8_t)newMode));
        Serial.println("Set mode to " + String((uint8_t)newMode));
      }
      else
      {
        request->send(200, "text/html", "Missing data.<br><a href=\"/\">Return to Home Page</a>");
      }
    }
      else request->send(200, "text/html", "Missing data.<br><a href=\"/\">Return to Home Page</a>"); });

  server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    String inputMessage;
    // GET input1 value on <ESP_IP>/set?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1))
    {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      EEPROM.writeString(MSG_OFFSET, inputMessage);
      EEPROM.writeByte(SENTINEL_OFFSET, SENTINEL_VALUE);
      EEPROM.commit();

      Serial.println(inputMessage);
      request->send(200, "text/html", "Set msg to '" + inputMessage + "'<br><a href=\"/\">Return to Home Page</a><br><a href=\"/run\">Leave upload mode</a>");
    }
    else
      request->send(200, "text/html", "Missing data.<br><a href=\"/\">Return to Home Page</a>"); });

  uploadMode = false;
  latched = false;
  running = true;
  touchButton.reset();
}

void loop(void)
{

  // Wait for connection
  if (!connected && WiFi.status() == WL_CONNECTED)
  {
    connected = true;
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    AsyncElegantOTA.begin(&server); // Start ElegantOTA
    server.begin();
    Serial.println("HTTP server started");
  }
  if (!running)
    return;
  // loop to blink without delay
  unsigned long currentMillis = millis();

  if (uploadMode)
  {
    display.setCursor(0, 0);
    display.setTextColor(WHITE, BLACK);
    display.clearDisplay();
    display.println(F("Upload"));
    display.print(WiFi.localIP());
    display.println(F("/update"));
    display.display();
  }
  else
  {
    if (renderer)
      renderer->update();
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

  if (!uploadMode)
  {
    if (sleepTimer > 10000)
    {
      // Go to sleep now
      Serial.println("Going to sleep now");
      display.clearDisplay();
      display.ssd1306_command(SSD1306_DISPLAYOFF);

      touchAttachInterrupt(T3, callback, Threshold);
      esp_sleep_enable_touchpad_wakeup();

      esp_deep_sleep_start();
    }
  }
  else
  {
    sleepTimer = 0;
  }

  touchButton.update();
  bool touched = touchButton.read();
  if (touchButton.changed())
  {
    if(renderer)
      renderer->press(touched);
    Serial.println(touched);
    if (!touched)
      latched = false;
  }
  if (!latched && touched && touchButton.currentDuration() > 2000)
  {
    latched = true;
    uploadMode = !uploadMode;
    if (!uploadMode)
    {
      digitalWrite(led, LOW);
      pullMessage();
    }
  }
}
