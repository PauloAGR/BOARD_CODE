void ConnectWiFi_STA(bool useStaticIP = false)
{
  Serial.println("");
  WiFi.mode(WIFI_STA);
  WiFi.begin(sta.SSID, sta.PASSWD);
  if (useStaticIP)
    WiFi.config(CharToIP(sta.IP_ADDRESS), CharToIP(sta.IP_GATEWAY), CharToIP(sta.IP_SUBNET));
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print('.');
  }

  Serial.println("");
  Serial.print("Iniciado STA:\t");
  Serial.println(sta.SSID);
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void ConnectWiFi_AP(bool useStaticIP = false)
{
  Serial.println("");
  WiFi.mode(WIFI_AP);
  while (!WiFi.softAP(sta.SSID, sta.PASSWD))
  {
    Serial.println(".");
    delay(100);
  }
  if (useStaticIP)
    WiFi.softAPConfig(CharToIP(ap.IP_ADDRESS), CharToIP(ap.IP_GATEWAY), CharToIP(ap.IP_SUBNET));

  Serial.println("");
  Serial.print("Iniciado AP:\t");
  Serial.println(ap.SSID);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
}