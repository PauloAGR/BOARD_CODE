/*
 * Copyright © Paulo Andrés Guerrero Ramírez
 * Refactored code
 */

#include <Arduino.h>
#include <WiFi.h>
#include "esp_wifi.h"
#include "ESPAsyncWebServer.h"
#include <PubSubClient.h>
#include "SPIFFS.h"
#include <ArduinoJson.h>
#include "time.h"
#include <ESPmDNS.h>

#include "DataVariables.hpp"
#include "Utils.hpp"
#include "WIFI.hpp"
#include "MQTT.hpp"
#include "Server.hpp"
#include "WebSocket.hpp"
#include "Sensors.hpp"
#include "Configutation.hpp"
SENSOR light;

void setup()
{
  strcpy(light.TYPE, "LIGHT");
  light.VALUE = 0;
  // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.begin(115200);
  Serial.println("Starting system...");

  // Begin LittleFS for ESP8266 or SPIFFS for ESP32
  fileSystemCheck();

  // Init to WIFI
  initWiFi();
  // attach AsyncWebSocket
  webSocketInit();

  // Serve files for Web Dashboard
  webServerInit();

  // Stablish conection to MQTT server
  enableMQTT();

  setTime();
}

void loop()
{
  // Read the LDR values continously
  basicSensorRead(light);
  // MQTT
  handleMqtt();
  // printLocalTime();
  delay(5000);
}
