/*
 * Copyright © Paulo Andrés Guerrero Ramírez
 * Refactored code
 */

#include <Arduino.h>
#include <WiFi.h>
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

void setup()
{
  // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.begin(115200);
  Serial.println("Starting system...");

  // Begin LittleFS for ESP8266 or SPIFFS for ESP32
  fileSystemCheck();

  // Connect to WIFI
  ConnectWiFi_STA();

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
  readLDR();

  // MQTT
  handleMqtt();
  // printLocalTime();
  delay(5000);
}
