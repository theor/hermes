/*
  Rui Santos
  Complete project details
   - Arduino IDE: https://RandomNerdTutorials.com/esp32-ota-over-the-air-arduino/
   - VS Code: https://RandomNerdTutorials.com/esp32-ota-over-the-air-vs-code/

  This sketch shows a Basic example from the AsyncElegantOTA library: ESP32_Async_Demo
  https://github.com/ayushsharma82/AsyncElegantOTA
*/

#include <Arduino.h>
#include <Wire.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "WifiConfig.h"
#include <SPI.h>
#include <Adafruit_SSD1306.h>
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

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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
        case RenderMode::TextRain:renderer = new TextRainRenderer();
            break;
        case RenderMode::TextAndBitmap:renderer = new TextRenderer(true);
            break;
        case RenderMode::Plant:renderer = new Plant::PlantRenderer();
            break;
        case RenderMode::Rain:renderer = new Rain::RainRenderer();
            break;
        default:renderer = new TextRenderer(false);
            break;
    }
    SPIFFS.mkdir(String("/") + renderer->getPrefix());
    sync_set_base(device, renderer->getPrefix());

    renderer->initTracks(device);
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

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
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

    touchButton.attach(T3);
    touchButton.interval(50); // interval in ms
    touchButton.reset();

    uploadButton.attach(T4);
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
        display.setTextColor(WHITE, BLACK);
        display.clearDisplay();
        display.setFont(nullptr);
        display.setTextWrap(true);
        display.println(F("Upload mode"));
        display.println(WiFi.localIP());
        display.print(F("Dbg: "));
        display.print(debugMode);

        display.display();
    }
    else
    {
        if (renderer)
            renderer->update(touched);
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
            display.clearDisplay();
            display.ssd1306_command(SSD1306_DISPLAYOFF);

            // touchAttachInterrupt(T2, callback, Threshold);
            touchAttachInterrupt(T3, callback, Threshold);
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
            display.clearDisplay();
            display.setCursor(0, 0);
            display.println(F("Connecting to wifi: "));
            display.println(SSID);
            display.display();
            if (!WiFi.reconnect())
            {
                WiFi.mode(WIFI_STA);
                WiFi.begin(SSID, PASSWORD);
            }
            while (WiFi.status() != WL_CONNECTED)
            {
                Serial.print('.');
                display.print('.');
                display.display();
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
        }
    }

    Serial.println(currentMillis);

    if(!uploadTouched)
    if (device)
    {
        rocket_update();
    }
    Serial.println("rocket update done");
}
