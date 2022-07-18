#include "IP.hpp"
#include "Log.hpp"

void IP::onWiFiEvent(WiFiEvent_t event) {
    Log.traceln(F("WiFi Event %d occured."), event);
    switch (event) {
    case ARDUINO_EVENT_WIFI_READY:
        Log.infoln(F("WiFi interface ready"));
        break;

    case ARDUINO_EVENT_WIFI_SCAN_DONE:
        Log.infoln(F("Completed scan for access points"));
        break;

    case ARDUINO_EVENT_WIFI_STA_START:
        Log.infoln(F(">>> Starting WiFi interface..."));
        Log.infoln(F("    --> Setting hostname to \"%s\""), HOSTNAME);
        WiFi.setHostname(HOSTNAME);
        Log.infoln(F("<<< WiFi interface has started."));
        break;

    case ARDUINO_EVENT_WIFI_STA_STOP:
        Log.warningln(F("!!! WiFi interface brought down."));
        break;
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        Log.infoln(F("*** WiFi has connected to AP."));
        break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        Log.warningln(F("!!! WiFi is disconnected from AP."));
        break;

    case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
      Log.infoln("Authentication mode of access point has changed");
      break;

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Log.infoln(F("*** Obtained IP Address:"));
      Log.infoln(F("    --> MAC Address:     %s"), WiFi.macAddress().c_str());
      Log.infoln(F("    --> SSID:            %s"), WiFi.SSID());
      Log.infoln(F("    --> Channel:         %lu, RSSI: %d"), WiFi.channel(),
                 WiFi.RSSI());
      Log.infoln(F("    --> IPv4 Address:    %s/%u"),
                 WiFi.localIP().toString().c_str(), WiFi.subnetCIDR());
      Log.infoln(F("    --> Gateway Address: %s"),
                 WiFi.gatewayIP().toString().c_str());
      break;

    case ARDUINO_EVENT_WIFI_STA_LOST_IP:
      Log.infoln("Lost IP address and IP address is reset to 0");
      break;

    case ARDUINO_EVENT_WPS_ER_SUCCESS:
      Log.infoln("WiFi Protected Setup (WPS): succeeded in enrollee mode");
      break;

    case ARDUINO_EVENT_WPS_ER_FAILED:
      Log.infoln("WiFi Protected Setup (WPS): failed in enrollee mode");
      break;

    case ARDUINO_EVENT_WPS_ER_TIMEOUT:
      Log.infoln("WiFi Protected Setup (WPS): timeout in enrollee mode");
      break;

    case ARDUINO_EVENT_WPS_ER_PIN:
      Log.infoln("WiFi Protected Setup (WPS): pin code in enrollee mode");
      break;

    case ARDUINO_EVENT_WIFI_AP_START:
      Log.infoln("WiFi access point started");
      break;

    case ARDUINO_EVENT_WIFI_AP_STOP:
      Log.infoln("WiFi access point  stopped");
      break;

    case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
      Log.infoln("Client connected");
      break;

    case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
      Log.infoln("Client disconnected");
      break;

    case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
      Log.infoln("Assigned IP address to client");
      break;

    case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED:
      Log.infoln("Received probe request");
      break;

    case ARDUINO_EVENT_WIFI_AP_GOT_IP6:
      Log.infoln("AP IPv6 is preferred");
      break;

    case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
      Log.infoln("STA IPv6 is preferred");
      break;

    case ARDUINO_EVENT_ETH_GOT_IP6:
      Log.infoln("Ethernet IPv6 is preferred");
      break;

    case ARDUINO_EVENT_ETH_START:
      Log.infoln(F(">>> Starting Ethernet interface..."));
      Log.infoln(F("    --> Setting hostname to \"%s\""), HOSTNAME);
      ETH.setHostname(HOSTNAME);
      Log.infoln(F("<<< Ethernet interface has started."));
      break;

    case ARDUINO_EVENT_ETH_STOP:
      Log.warningln(F("!!! Ethernet interface brought down."));
      Log.warningln(F("!!! Trying WiFi reconnection."));
      WiFi.reconnect();
      break;

    case ARDUINO_EVENT_ETH_CONNECTED:
      Log.infoln(F("*** Ethernet link is up."));
      break;

    case ARDUINO_EVENT_ETH_DISCONNECTED:
      Log.warningln(F("!!! ETH Disconnected!"));
      Log.warningln(F("!!! Trying WiFi reconnection..."));
      WiFi.reconnect();
      break;

    case ARDUINO_EVENT_ETH_GOT_IP:
      Log.infoln(F("*** Obtained IP Address:"));
      Log.infoln(F("    --> MAC Address:     %s"), ETH.macAddress().c_str());
      Log.infoln(F("    --> Link Speed:      %dMbps, %s"), ETH.linkSpeed(),
                 (ETH.fullDuplex() ? "Full Duplex" : "Half Duplex"));
      Log.infoln(F("    --> IPv4 Address:    %s/%u"),
                 ETH.localIP().toString().c_str(), ETH.subnetCIDR());
      Log.infoln(F("    --> Gateway Address: %s"),
                 ETH.gatewayIP().toString().c_str());
      Log.infoln(F("*** Disconnecting WiFi..."));
      if (WiFi.isConnected()) {
        WiFi.disconnect();
      }
      break;

    default:
      break;
    }
}

void IP::init() {
    WiFi.onEvent(onWiFiEvent);
    WiFi.begin(IP::SSID, IP::PASSPHRASE);
}

void IP::wait() {}
void IP::registerCUI() {}
