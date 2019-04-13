#ifndef __WEBSOCKETCLIENTUPGRADED_H_
#define __WEBSOCKETCLIENTUPGRADED_H_

#include <ArduinoHttpClient.h>

class WebSocketClient250 : public WebSocketClient
{
public:
  WebSocketClient250(WiFiClientSecure &wiFiClient, const char *host, uint16_t port)
      : WebSocketClient(wiFiClient, host, port)
  {
  }

  int connect(CONST IPAddress &ip, uint16_t port)
  {
    return WebSocketClient::connect(ip, port);
  }

  bool flush(unsigned int maxWaitMs = 0)
  {
    WebSocketClient::flush();
    return true;
  }

  bool stop(unsigned int maxWaitMs = 0)
  {
    WebSocketClient::stop();
    return true;
  }
};

#endif
