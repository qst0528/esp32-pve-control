#include <Arduino.h>
#include <WiFi.h>
#include <ETH.h>

namespace IP {
  extern char     const* HOSTNAME;
  extern uint16_t        OTA_PORT;
  extern char     const* SSID;
  extern char     const* PASSPHRASE;
  extern void onWiFiEvent(WiFiEvent_t);
  extern void init();
  extern void wait();
  extern void registerCUI();
} // namespace IP
