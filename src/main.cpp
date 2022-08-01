/*
  Rui Santos
  Complete project details
   - Arduino IDE: https://RandomNerdTutorials.com/esp32-ota-over-the-air-arduino/
   - VS Code: https://RandomNerdTutorials.com/esp32-ota-over-the-air-vs-code/

  This sketch shows a Basic example from the AsyncElegantOTA library: ESP32_Async_Demo
  https://github.com/ayushsharma82/AsyncElegantOTA
*/

//#include "TFT_config.h"

#include <Arduino.h>
#include <Wire.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "WifiConfig.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include "sprite.h"
#include <SPI.h>
#include <EEPROM.h>

#include "bitmap.h"
#include "global.h"

#include "EmbeddedServer.h"
#include "renderer.h"
#include "renderers/plant.h"
#include "renderers/rain.h"
#include "TouchButton.h"
#include "elapsedMillis.h"

#include "rocket.h"

TFT_eSPI screen = TFT_eSPI();

Sprite display = Sprite(&screen);
TouchButton touchButton(Threshold);
TouchButton uploadButton(Threshold);

// variabls for blinking an LED with Millis
unsigned long previousMillis = 0; // will store last time LED was updated
const long interval = 300;        // interval at which to blink (milliseconds)
int ledState = LOW;               // ledState used to set the LED

bool debugMode = false;
bool uploadMode = false;
bool latched = false;
bool running = false;
bool connected = false;

RenderMode mode = RenderMode::TextAndBitmap;

AsyncWebServer server(80);

String payload;
elapsedMillis sleepTimer;
Renderer *renderer;

#define SSD1351_CMD_DISPLAYOFF 0xAE     ///< See datasheet
#define SSD1351_CMD_DISPLAYON 0xAF      ///< See datasheet

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
    Serial.println((int) mode);
    switch (mode)
    {
        case RenderMode::TextRain:renderer = new TextRainRenderer(&display);
            break;
        case RenderMode::TextAndBitmap:renderer = new TextRenderer(&display,true);
            break;
        case RenderMode::Plant:renderer = new Plant::PlantRenderer(&display);
            break;
        case RenderMode::Rain:renderer = new Rain::RainRenderer(&display);
            break;
        default:renderer = new TextRenderer(&display,false);
            break;
    }
    SPIFFS.mkdir(String("/") + renderer->getPrefix());
    sync_set_base(device, renderer->getPrefix());

    renderer->initTracks(device);
    renderer->start();
}

//const uint8_t COMMAND_ON[] PROGMEM = {
//        SSD
//};

void pullMessage()
{
    display.writecommand(SSD1351_CMD_DISPLAYON);
//    display.setFont(nullptr);
//    display.setTextColor(WHITE, BLACK);

    Serial.print("eeprom size:");
    Serial.println(EEPROM.length());
    if (EEPROM.readByte(SENTINEL_OFFSET) != SENTINEL_VALUE)
        payload = F("No data");
    else
    {
        payload = EEPROM.readString(MSG_OFFSET);
        mode = (RenderMode) EEPROM.readByte(MODE_OFFSET);
    }
    if (payload.length() == 0)
        payload = F("No message");
    Serial.println(payload + " " + String((int) mode));

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
    screen.init();
    screen.setRotation(1);
    screen.fillScreen(TFT_BLUE);
    screen.drawPixel(10, 10, TFT_RED);

    display.setColorDepth(16);
    display.createSprite(TFT_WIDTH, TFT_HEIGHT);
}

void rocketMode()
{
    SPIFFS.begin(true);
    if (debugMode)
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(SSID, PASSWORD);
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.print('.');
            delay(500);
        }
    }
    if (!rocket_init())
        return;
}

void setup(void)
{
    running = false;
    connected = false;
    pinMode(LED_PIN, OUTPUT);
    EEPROM.begin(512);
    debugMode = EEPROM.readByte(DEBUGMODE_OFFSET) == 1;

    touchButton.attach(T8);
    touchButton.interval(50); // interval in ms
    touchButton.reset();

    uploadButton.attach(T9);
    uploadButton.interval(50); // interval in ms
    uploadButton.reset();

    Serial.begin(115200);

    initDisplay();


    rocketMode();
    pullMessage();

    setupServer();

    uploadMode = false;
    latched = false;
    running = true;
    touchButton.reset();
    uploadButton.reset();

}

void loop(void)
{
    if (!running)
        return;
    // loop to blink without delay
    unsigned long currentMillis = millis();
    touchButton.update();
    bool touched = touchButton.read();

    if (uploadMode)
    {
        display.setCursor(0, 0);
        display.setTextColor(TFT_WHITE, TFT_BLACK);
        display.fillScreen(TFT_BLACK);
        display.setTextWrap(true);
        display.println(F("Upload mode"));
        display.println(WiFi.localIP());
        display.print(F("Dbg: "));
        display.println(debugMode);
        display.print(F("Mode: "));
        display.println((int)mode);
    }
    else
    {
        if (renderer)
        {
            renderer->update(touched);
//            if(renderer->inverted) { screen.writecommand(TFT_INVON); renderer->inverted = false; }
        }
    }

    if (uploadMode && currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        ledState = not(ledState);
        digitalWrite(LED_PIN, ledState);
    }

    if (!uploadMode)
    {
        if (renderer && renderer->sleepTimerResetRequested())
            sleepTimer = 0;
        if (!debugMode && sleepTimer > 10000)
        {
            // Go to sleep now
            Serial.println("Going to sleep now");
            display.writecommand(SSD1351_CMD_DISPLAYOFF);

            // touchAttachInterrupt(T2, callback, Threshold);
            touchAttachInterrupt(T8, callback, Threshold);
            esp_sleep_enable_touchpad_wakeup();

            esp_deep_sleep_start();
        }
    }
    else
    {
        sleepTimer = 0;
    }
    if (touchButton.changed())
    {
        if (renderer)
            renderer->press(touched);
    }

    uploadButton.update();
    bool uploadTouched = uploadButton.read();
    if (uploadButton.changed())
    {
        digitalWrite(LED_PIN, uploadTouched);

        Serial.println(uploadTouched);
        if (!uploadTouched)
            latched = false;
    }
    if (!latched && uploadTouched && uploadButton.currentDuration() > 1000)
    {
        latched = true;
        uploadMode = !uploadMode;
        if (!uploadMode)
        {
            digitalWrite(LED_PIN, LOW);
            if (!debugMode)
            {
                server.end();
                WiFi.mode(WIFI_OFF);
            }
            pullMessage();
        }
        else
        {
            display.fillScreen(TFT_BLACK);
            display.setCursor(0, 0);
            display.println(F("Connecting to wifi: "));
            display.println(SSID);
            display.pushSprite(0,0);
            if (!WiFi.reconnect())
            {
                WiFi.mode(WIFI_STA);
                WiFi.begin(SSID, PASSWORD);
            }
            while (WiFi.status() != WL_CONNECTED)
            {
                Serial.print('.');
                display.print('.');
                display.pushSprite(0,0);
                delay(500);
            }

            server.begin();
            Serial.println("");
            Serial.print("Connected to ");
            Serial.println(SSID);
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
            AsyncElegantOTA.begin(&server); // Start ElegantOTA
            Serial.println("HTTP server started");
            Serial.println("    connect rocket");
            sync_tcp_connect(device, ROCKET_HOST_IP, SYNC_DEFAULT_PORT);
            display.println();
            display.println("Rocket connected");
        }
    }

//    Serial.println(currentMillis);

    if(!uploadTouched)
    if (device)
    {
        rocket_update();
    }
//    Serial.println("rocket update done");
    display.pushSprite(0,0);
}
