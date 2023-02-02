#define LIGHT_SENSOR_PIN 36 // ESP32 pin GIOP36 (ADC0)

struct tm timeinfo;

struct DEVICE
{
    char ID[30] = "grupo_1";
    char name[30] = "ESP32_PARZIVAL";
} device;

struct STA
{
    char SSID[30] = "KNIGHTS_FORTRESS";
    char PASSWD[30] = "covenant";
    char IP_ADDRESS[15] = "192.168.1.210";
    char IP_GATEWAY[15] = "192.168.1.1";
    char IP_SUBNET[15] = "192.168.1.0";
} sta;

struct AP
{
    char SSID[30] = "ESP_KNIGHTS_FORTRESS";
    char PASSWD[30] = "covenant";
    char IP_ADDRESS[15] = "192.168.1.210";
    char IP_GATEWAY[15] = "192.168.1.1";
    char IP_SUBNET[15] = "192.168.1.0";
} ap;

struct MQTT
{
    char BROKER_ADRESS[15] = "192.168.1.92";
    uint16_t PORT = 1883;
    char CLIENT_ID[30] = "grupo_1";
    char CLIENT_USER[30] = "grupo_1";
    char CLIENT_PASS[30] = "grupo_1";
    char TOPIC[30] = "ESP32/ID/GRUPO_1";
} mqtt;

char ntpServer[30] = "co.pool.ntp.org";

WiFiClient espHost;
PubSubClient espMQTTClient(espHost);

AsyncWebServer server(80);
AsyncWebSocket webSocket("/ws");

// String subsTopic = "esp32/id/grupo1";
//  String content = "";
String payload;
int sensorVal = 0;
