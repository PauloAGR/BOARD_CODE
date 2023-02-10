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
    server.on("/assets/index-2613cd82.css", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/assets/index-2613cd82.css.gz", "text/css");
                response->addHeader("Content-Encoding", "gzip");
                response->addHeader("Cache-Control", "max-age=86400"); // 1 día
                request->send(response); });

    server.on("/assets/index-8989682a.css", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/assets/index-8989682a.css.gz", "text/css");
                response->addHeader("Content-Encoding", "gzip");
                response->addHeader("Cache-Control", "max-age=86400"); // 1 día
                request->send(response); });

    // Route for root index.js
    server.on("/assets/index-c3154a19.js", HTTP_GET, [](AsyncWebServerRequest *request)
              {
              AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/assets/index-c3154a19.js.gz", "application/javascript");
              response->addHeader("Content-Encoding","gzip");
              response->addHeader("Cache-Control","max-age=86400"); // 1 día
              request->send(response); });
    server.onNotFound(notFound);

    server.on("/assets/index-9fbb2826.js", HTTP_GET, [](AsyncWebServerRequest *request)
              {
              AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/assets/index-9fbb2826.js.gz", "application/javascript");
              response->addHeader("Content-Encoding","gzip");
              response->addHeader("Cache-Control","max-age=86400"); // 1 día
              request->send(response); });
    server.onNotFound(notFound);

    // Route for root files
    // server.on("/assets/Logo_de_la_Universidad_del_Cauca-a892d660.svg", HTTP_GET, [](AsyncWebServerRequest *request)
    //           {
    //           AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/assets/Logo_de_la_Universidad_del_Cauca-a892d660.svg.gz", "image/svg+xml");
    //           response->addHeader("Content-Encoding","gzip");
    //           response->addHeader("Cache-Control","max-age=86400"); // 1 día
    //           request->send(response); });
    // server.onNotFound(notFound);

    server.on("/assets/logo_unicauca-e8373cfe.png", HTTP_GET, [](AsyncWebServerRequest *request)
              {
              AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/assets/logo_unicauca-e8373cfe.png.gz", "image/png");
              response->addHeader("Content-Encoding","gzip");
              response->addHeader("Cache-Control","max-age=86400"); // 1 día
              request->send(response); });
    server.onNotFound(notFound);

    // Start the server
    server.begin();
}