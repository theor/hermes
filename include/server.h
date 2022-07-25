#pragma once

#include <ESPAsyncWebServer.h>
#include <global.h>
#include <EEPROM.h>

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


void pullMessage();
void setRenderer(RenderMode newMode);

void setupServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", index_html); });
    server.on("/run", HTTP_GET, [](AsyncWebServerRequest *request)
              { 
    uploadMode = false;
        digitalWrite(LED_PIN, LOW);
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
}