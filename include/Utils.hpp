IPAddress CharToIP(const char *str)
{
    uint8_t ip[4];
    sscanf(str, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[1], &ip[2], &ip[3]);
    return IPAddress(ip[0], ip[1], ip[2], ip[3]);
}

void fileSystemCheck()
{
    if (!SPIFFS.begin())
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
}

void setTime()
{
    configTzTime(ntp.TIME_ZONE, ntp.SERVER_1, ntp.SERVER_2, ntp.SERVER_3);
    // configTime(0, 0, ntp.SERVER);
    // setenv("TZ", ntp.TIME_ZONE, 1); //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
    // tzset();
    // printLocalTime();
}

void InitMDNS()
{
    if (!MDNS.begin(device.ID))
    {
        Serial.println("Error iniciando mDNS");
    }
    Serial.println("mDNS iniciado");
}

// void onMqttReceived(char *topic, byte *payload, unsigned int length)
// {
//   Serial.print("Received on ");
//   Serial.print(topic);
//   Serial.println(": ");

//   content = "";
//   for (size_t i = 0; i < length; i++)
//   {
//     content.concat((char)payload[i]);
//   }
//   // Serial.print(content);
//   // Serial.println();
//   StaticJsonDocument<300> doc;
//   DeserializationError error = deserializeJson(doc, content);
//   if (error)
//     return;
//   serializeJsonPretty(doc, Serial);
//   String json = "";
//   serializeJson(doc, json);
//   //webSocket.printfAll((json).c_str());
//   //  unsigned long data = doc["value"];
//   //  Serial.print("Millis:");
// }

// String converToJSON(int c_keys, char *keys, char *values)
// {
//   const size_t CAPACITY = JSON_OBJECT_SIZE(c_keys);
//   DynamicJsonDocument doc(CAPACITY);
// }

// void splitString(char *buf, JsonDocument doc)
// {
//   const char *p = buf, *q;
//   // int num_tokens = 1;

//   while ((q = strchr(p, '#')) != NULL)
//   {
//     char destino[strlen(q) + 1];
//     strncpy(destino, p, strlen(p) - strlen(q));
//     printf("destino: %s\n", destino);
//     p = q + 1;
//   }
// }

// void printLocalTime()
// {
//   struct tm timeinfo;
//   if (!getLocalTime(&timeinfo))
//   {
//     Serial.println("Failed to obtain time");
//     return;
//   }
//   Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
//   Serial.print("Day of week: ");
//   Serial.println(&timeinfo, "%A");
//   Serial.print("Month: ");
//   Serial.println(&timeinfo, "%B");
//   Serial.print("Day of Month: ");
//   Serial.println(&timeinfo, "%d");
//   Serial.print("Year: ");
//   Serial.println(&timeinfo, "%Y");
//   Serial.print("Hour: ");
//   Serial.println(&timeinfo, "%H");
//   Serial.print("Hour (12 hour format): ");
//   Serial.println(&timeinfo, "%I");
//   Serial.print("Minute: ");
//   Serial.println(&timeinfo, "%M");
//   Serial.print("Second: ");
//   Serial.println(&timeinfo, "%S");
//   Serial.println("Time variables");
//   char timeHour[3];
//   strftime(timeHour, 3, "%H", &timeinfo);
//   Serial.println(timeHour);
//   char timeWeekDay[10];
//   strftime(timeWeekDay, 10, "%A", &timeinfo);
//   Serial.println(timeWeekDay);
//   Serial.println();
// }