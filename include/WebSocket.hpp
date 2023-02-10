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

void webSocketInit()
{
    webSocket.onEvent(onEvent);
    server.addHandler(&webSocket);
}