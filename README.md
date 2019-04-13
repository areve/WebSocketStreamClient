# WebSocketStreamClient

A WebSocketClient that implements Client.h so that the PubCubClient MQTT library can use it - with wss or ws.

## Dependencies

* [ArduinoHttpClient 0.4.0](https://github.com/arduino-libraries/ArduinoHttpClient) and all of it's dependencys. Because this works with esp8266/2.4.2 but not with esp8266/2.5.0, use the supplied WebSocketClient250 class instead.

Tested with esp8266/2.5.0 Board libraries. There is an example node.js server that you can use here with this library at [web-socket-mqtt](https://github.com/areve/web-socket-mqtt).

## Usage

See examples folder for a complete program.

```cpp

void onMqttPublish(char *topic, byte *payload, unsigned int length)
{
  // handle mqtt messages here
}

WiFiClientSecure wiFiClient;
WebSocketClient250 wsClient(wiFiClient, host, port);
WebSocketStreamClient wsStreamClient(wsClient, path);
PubSubClient mqtt(wsStreamClient);

wiFiClient.setFingerprint(fingerprint);
mqtt.setCallback(onMqttPublish);

if (mqtt.connect("your_identifier"))
{
  mqtt.publish("topic1", "hello world");
  mqtt.subscribe("topic2");
}

```