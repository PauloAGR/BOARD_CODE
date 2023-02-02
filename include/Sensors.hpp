void readLDR()
{
    // reads the input on analog pin (value between 0 and 4095)
    int analogValue = analogRead(LIGHT_SENSOR_PIN);
    if (!analogValue != sensorVal)
    {

        if (!getLocalTime(&timeinfo))
        {
            Serial.println("Failed to obtain time");
            return;
        }
        char time[18];
        strftime(time, 18, "%y/%m/%d %H:%M:%S", &timeinfo);
        DynamicJsonDocument doc(255);
        sensorVal = analogValue;
        doc["time"] = time;
        doc["sensor"] = "light";
        doc["value"] = sensorVal;
        serializeJsonPretty(doc, Serial);
        publisMqtt(doc);
        String output;
        serializeJson(doc, output);
        webSocket.printfAll(output.c_str());
    }
}