// #define LIGHT_SENSOR_PIN 36 // ESP32 pin GIOP36 (ADC0)

wifi_sta_list_t wifi_sta_list;
tcpip_adapter_sta_list_t adapter_sta_list;
tcpip_adapter_sta_info_t station;

struct tm timeinfo;
struct WIFI_CONF
{
    char SSID[30] = "KNIGHTS_FORTRESS";
    char PASSWD[30] = "covenant";
    bool STATIC = false;
    char IP_ADDRESS[15] = "192.168.1.10";
    char IP_GATEWAY[15] = "192.168.1.1";
    char IP_SUBNET[15] = "192.168.1.0";
    uint8_t connect_attemp = 0;
};

struct MQTT
{
    char BROKER_ADRESS[15] = "192.168.243.34";
    uint16_t PORT = 1883;
    char CLIENT_ID[30] = "grupo_1";
    char CLIENT_USER[30] = "grupo_1";
    char CLIENT_PASS[30] = "grupo_1";
    char TOPIC[30] = "ESP32/ID/GRUPO_1";
    uint8_t connect_attemp = 0;
} mqtt;

struct NTP
{
    char SERVER_1[30] = "1.co.pool.ntp.org";
    char SERVER_2[30] = "2.south-america.pool.ntp.org";
    char SERVER_3[30] = "3.south-america.pool.ntp.org";
    char TIME_ZONE[30] = "EST5EDT,M3.2.0,M11.1.0";
} ntp;
struct DEVICE
{
    char ID[30] = "grupo_1";
    char NAME[30] = "morales_guerrero";
    char BUILD[10] = "1.0";
    wifi_mode_t WIFI_MODE = WIFI_MODE_STA;
    uint8_t SENSOR_Q = 1;
    WIFI_CONF ap, sta;
} device;
struct SENSOR
{
    uint8_t PIN = 36;
    char TYPE[15] = "LIGHT";
    float VALUE = 0;
};
// String subsTopic = "esp32/id/grupo1";
//  String content = "";

String payload = "";