/*
 * Copyright © Paulo Andrés Guerrero Ramírez
 *
 */

#include <Arduino.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 * This
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-light-sensor
 */

#define LIGHT_SENSOR_PIN 36 // ESP32 pin GIOP36 (ADC0)

const char *ssid = "KNIGHTS_FORTRESS";
const char *password = "covenant";

AsyncWebServer server(80);
AsyncWebSocket webSocket("/ws");

static int sensorVal = 0;

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
  if (type == WS_EVT_CONNECT)
  {
    // client connected
    Serial.println("Client connected....");
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    client->ping();
  }
  else if (type == WS_EVT_DISCONNECT)
  {
    // client disconnected
    Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  }
  else if (type == WS_EVT_ERROR)
  {
    // error was received from the other end
    Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
  }
  else if (type == WS_EVT_PONG)
  {
    // pong message was received (in response to a ping request maybe)
    Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char *)data : "");
  }
  else if (type == WS_EVT_DATA)
  {
    // do nothing as client is not sending message to server
    Serial.printf("ws[%s][%u] data received\n", server->url(), client->id());
  }
}

void readLDR()
{
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  if (analogValue != sensorVal)
  {
    sensorVal = analogValue;
    webSocket.printfAll(std::to_string(sensorVal).c_str());
  }
}

void setup()
{

  Serial.begin(115200);
  Serial.println("Starting the Real-time Chart display of Sensor Readings ..");

  // Begin LittleFS for ESP8266 or SPIFFS for ESP32
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("WiFi Failed!\n");
    return;
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // attach AsyncWebSocket
  webSocket.onEvent(onEvent);
  server.addHandler(&webSocket);

  // Route for root index.html
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
              AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/index.html.gz", "text/html");
                response->addHeader("Content-Encoding", "gzip");
                response->addHeader("Cache-Control", "max-age=86400"); // 1 día
                request->send(response); });

  // Route for root index.css
  server.on("/assets/index-2613cd82.css", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/assets/index-2613cd82.css.gz", "text/css");
        response->addHeader("Content-Encoding", "gzip");
        response->addHeader("Cache-Control", "max-age=86400"); // 1 día
        request->send(response); });

  // Route for root index.js
  server.on("/assets/index-9fbb2826.js", HTTP_GET, [](AsyncWebServerRequest *request)
            {
        AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/assets/index-9fbb2826.js.gz", "application/javascript");
        response->addHeader("Content-Encoding","gzip");
        response->addHeader("Cache-Control","max-age=86400"); // 1 día
        request->send(response); });

  server.onNotFound(notFound);

  // Start the server
  server.begin();
}

void loop()
{
  // Read the LDR values continously
  readLDR();
  delay(10000);
}
