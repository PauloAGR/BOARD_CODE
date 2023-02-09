AsyncWebServer server(80);
AsyncWebSocket webSocket("/ws");

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

void webServerInit()
{
    // Route for root index.html
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { 
              AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/index.html.gz", "text/html");
                response->addHeader("Content-Encoding", "gzip");
                response->addHeader("Cache-Control", "max-age=86400"); // 1 día
                request->send(response); });

    // Route for root index.css
    // server.on("/assets/index-2613cd82.css", HTTP_GET, [](AsyncWebServerRequest *request)
    //           {
    //             AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/assets/index-2613cd82.css.gz", "text/css");
    //             response->addHeader("Content-Encoding", "gzip");
    //             response->addHeader("Cache-Control", "max-age=86400"); // 1 día
    //             request->send(response); });

    // Route for root index.js
    server.on("/assets/index-e3e6aa6b.js", HTTP_GET, [](AsyncWebServerRequest *request)
              {
              AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/assets/index-e3e6aa6b.js.gz", "application/javascript");
              response->addHeader("Content-Encoding","gzip");
              response->addHeader("Cache-Control","max-age=86400"); // 1 día
              request->send(response); });

    server.onNotFound(notFound);

    // Start the server
    server.begin();
}