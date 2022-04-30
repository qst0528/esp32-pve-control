#include "IP.hpp"
#include "Log.hpp"

void IP::onWiFiEvent(WiFiEvent_t event)
{
  switch (event)
    {
    case SYSTEM_EVENT_ETH_START:
      Log.infoln(F(">>> Starting Ethernet interface..."));
      Log.infoln(F("    -> Setting hostname to \"%s\""), HOSTNAME);
      ETH.setHostname(HOSTNAME);
      Log.infoln(F("<<< Ethernet interface has started."));
      break;
    case SYSTEM_EVENT_STA_START:
      Log.infoln(F(">>> Starting WiFi interface..."));
      Log.infoln(F("    -> Setting hostname to \"%s\""), HOSTNAME);
      WiFi.setHostname(HOSTNAME);
      Log.infoln(F("<<< WiFi interface has started."));
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      Log.infoln(F("*** Ethernet phy link is up."));
      break;
    case SYSTEM_EVENT_STA_CONNECTED:
      Log.infoln(F("*** WiFi has connected to AP."));
      break;
    case SYSTEM_EVENT_ETH_GOT_IP:
      Log.infoln(F("*** Acquired IP Address:"));
      Log.infoln(F("    -> MAC Address:     %s"), ETH.macAddress().c_str());
      Log.infoln(F("    -> Link Speed:      %dMbps, %s"), ETH.linkSpeed(),(ETH.fullDuplex() ? "Full Duplex" : "Half Duplex"));
      Log.infoln(F("    -> IPv4 Address:    %s/%u"), ETH.localIP().toString().c_str(), ETH.subnetCIDR());
      Log.infoln(F("    -> Gateway Address: %s"), ETH.gatewayIP().toString().c_str());
      if (WiFi.isConnected()) {
	WiFi.disconnect();
      }
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      Log.infoln(F("*** Acquired IP Address:"));
      Log.infoln(F("    -> MAC Address:     %s"), WiFi.macAddress().c_str());
      Log.infoln(F("    -> SSID:            %s"), WiFi.SSID());
      Log.infoln(F("    -> Channel:         %lu, RSSI: %d"), WiFi.channel(), WiFi.RSSI());
      Log.infoln(F("    -> IPv4 Address:    %s/%u"), WiFi.localIP().toString().c_str(), WiFi.subnetCIDR());
      Log.infoln(F("    -> Gateway Address: %s"), WiFi.gatewayIP().toString().c_str());
      break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
      Log.warningln(F("!!! ETH Disconnected!"));
      WiFi.reconnect();
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Log.warningln(F("!!! WiFi is disconnected from AP."));
      break;
    case SYSTEM_EVENT_ETH_STOP:
      Log.warningln(F("!!! ETH brought down."));
      WiFi.reconnect();
      break;
    case SYSTEM_EVENT_STA_STOP:
      Log.warningln(F("!!! ETH brought down."));
      break;
    default:
      break;
    }
}

void IP::init() {}
void IP::wait() {}
void IP::registerCUI() {}
