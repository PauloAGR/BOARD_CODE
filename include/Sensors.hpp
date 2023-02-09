void basicSensorRead(SENSOR sensor)
{
    // reads the inpulight_valuet on analog pin (value between 0 and 4095)
    float analogValue = analogRead(sensor.PIN);
    if (analogValue != sensor.VALUE)
    {
        if (!getLocalTime(&timeinfo))
        {
            Serial.println("Failed to obtain time");
            return;
        }
        char time[20];
        strftime(time, 20, "%y/%m/%d %H:%M:%S", &timeinfo);
        DynamicJsonDocument doc(128);
        sensor.VALUE = analogValue;
        doc["sensor"] = sensor.TYPE;
        doc["time"] = time;
        doc["value"] = sensor.VALUE;
        // serializeJsonPretty(doc, Serial);
        publisMqtt(doc);
        String output = "";
        serializeJson(doc, output);
        webSocket.printfAll(output.c_str());
    }
}