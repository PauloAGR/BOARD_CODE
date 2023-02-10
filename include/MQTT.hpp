WiFiClient espHost;
PubSubClient espMQTTClient(espHost);

void enableMQTT()
{
    espMQTTClient.setServer(mqtt.BROKER_ADRESS, mqtt.PORT);
}

// void suscribeMqtt()
// {
//     espMQTTClient.subscribe("esp32/#");
// }

void connectMqtt()
{
    while (!espMQTTClient.connected())
    {
        Serial.print("Starting MQTT connection...");
        if (espMQTTClient.connect(mqtt.CLIENT_ID, mqtt.CLIENT_USER, mqtt.CLIENT_PASS))
        {
            Serial.println("MQTT connection established.\n");
            // suscribeMqtt();
        }
        else
        {
            Serial.println("Failed MQTT connection, rc=");
            Serial.print(espMQTTClient.state());
        }
    }
}

void publisMqtt(DynamicJsonDocument doc)
{
    payload = "";
    serializeJson(doc, payload);
    espMQTTClient.publish(mqtt.TOPIC, (char *)payload.c_str());
}

void handleMqtt()
{
    if (!espMQTTClient.connected() && mqtt.connect_attemp < 10)
    {
        connectMqtt();
        mqtt.connect_attemp++;
    }
    espMQTTClient.loop();
}