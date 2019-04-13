#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "WebSocketStreamClient.h"
#include "WebSocketClient250.h"

#define DEBUG_MAIN(...) Serial.printf(__VA_ARGS__)

#ifndef DEBUG_MAIN
#define DEBUG_MAIN(...)
#endif

// config
const char *ssid = "YOURSSID";
const char *password = "YOURPASSWORD";
const char *host = (char *)"web-socket-mqtt.herokuapp.com";
const int port = 443;
const char *fingerprint = "08 3B 71 72 02 43 6E CA ED 42 86 93 BA 7E DF 81 C4 BC 62 30";
const char *path = (char *)"/mqtt";

// globals
unsigned int counter = 0;
unsigned long lastPublishTime = 0;
unsigned long publishInterval = 1000;
uint8_t buffer[1000];

void onMqttPublish(char *topic, byte *payload, unsigned int length)
{
  DEBUG_MAIN("received %s %.*s\n", topic, length, payload);
}

WiFiClientSecure wiFiClient;
WebSocketClient250 wsClient(wiFiClient, host, port);
WebSocketStreamClient wsStreamClient(wsClient, path);
PubSubClient mqtt(wsStreamClient);

void setup()
{
  Serial.begin(9600);
  delay(2000);

  DEBUG_MAIN("WiFi connecting to %s\n", ssid);
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    DEBUG_MAIN(".");
    delay(500);
  }
  DEBUG_MAIN("\nWiFi connected to %s\n", WiFi.SSID().c_str());

  wiFiClient.setFingerprint(fingerprint);
  mqtt.setCallback(onMqttPublish);

  DEBUG_MAIN("mqtt connecting\n");
  if (mqtt.connect("topic1"))
  {
    DEBUG_MAIN("mqtt connected OK\n");
    mqtt.publish("log", "hello world");
    mqtt.subscribe("topic1");
  }
}

void loop()
{
  mqtt.loop();
  if (lastPublishTime + publishInterval < millis())
  {
    lastPublishTime = millis();
    DEBUG_MAIN("tick %d\n", ++counter);
    if (mqtt.connected())
    {
      String msg = (String("esp8266 counter ") + String(counter));
      mqtt.publish("log", msg.c_str());
    }
  }
}
