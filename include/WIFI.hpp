// void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
// {
//     Serial.println("WiFi connected....TEST");
//    WiFi.
//     //Serial.println(IP2STR(info.wifi_ap_staipassigned.ip));
// }

void enableWiFi_STA(bool useStaticIP = false)
{
    // Serial.println("");
    //   WiFi.mode(WIFI_STA);
    WiFi.begin(device.sta.SSID, device.sta.PASSWD);
    if (useStaticIP)
        WiFi.config(CharToIP(device.sta.IP_ADDRESS), CharToIP(device.sta.IP_GATEWAY), CharToIP(device.sta.IP_SUBNET));
    Serial.print("INICIANDO STA");
    while (WiFi.status() != WL_CONNECTED && device.sta.connect_attemp < 60)
    {
        Serial.print(".");
        delay(100);
        device.sta.connect_attemp++;
    }
    if (device.sta.connect_attemp < 60)
    {
        Serial.println("");
        Serial.print("Iniciado STA:\t");
        Serial.println(device.sta.SSID);
        Serial.print("IP address:\t");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.print("ERROR INIT WIFI_STA");
    }
}

void enableWiFi_AP(bool useStaticIP = false)
{
    // Serial.println("");
    //    WiFi.mode(WIFI_AP);
    if (useStaticIP)
        WiFi.softAPConfig(CharToIP(device.ap.IP_ADDRESS), CharToIP(device.ap.IP_GATEWAY), CharToIP(device.ap.IP_SUBNET));
    Serial.print("INICIANDO SOFT_AP");
    while (!WiFi.softAP(device.ap.SSID, device.ap.PASSWD) && device.ap.connect_attemp < 60)
    {
        Serial.print(".");
        delay(100);
        device.ap.connect_attemp++;
    }
    if (device.ap.connect_attemp < 60)
    {
        //WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED);
        Serial.println("");
        Serial.print("Iniciado AP:\t");
        Serial.println(device.ap.SSID);
        Serial.print("IP address:\t");
        Serial.println(WiFi.softAPIP());
    }
    else
    {
        Serial.print("ERROR INIT SOFT_AP");
    }
}

void initWiFi()
{
    Serial.println("WIFI_MODE: " + device.WIFI_MODE);
    WiFi.mode(device.WIFI_MODE);
    if (device.WIFI_MODE == 1)
    {
        enableWiFi_STA(device.sta.STATIC);
    }
    else if (device.WIFI_MODE == 2)
    {
        enableWiFi_AP(device.sta.STATIC);
    }
    else if (device.WIFI_MODE == 3)
    {
        enableWiFi_STA(device.sta.STATIC);
        strcpy(device.ap.SSID, "ESP_KNIGHTS-FORTRESS");
        enableWiFi_AP(device.ap.STATIC);
    }
    else
    {
        Serial.println("WIFI ERROR");
    }
}