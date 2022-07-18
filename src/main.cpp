#include "config.hpp"

#include <HTTPClient.h>
#include <WiFiClientSecure.h>

namespace {
void serialSetup(HardwareSerial &serial, unsigned long baud) {
  serial.begin(baud);
  serial.println(F("Booting PVE Control..."));
}
} // namespace

void setup() {
  serialSetup(Serial, 115200);
  LOG::setup();
  CUI::attach();
  CUI::registerCUI();
  IP::init();
  delay(5000);
}

// put your setup code here, to run once:
void loop() {
  shell.executeIfInput();
  // put your main code here, to run repeatedly:

  WiFiClientSecure *client = new WiFiClientSecure;
  client -> setCACert( (char *) SSL::root_ca_cert_start );

  if(client) {

      {
          HTTPClient https;

          if (https.begin(*client, "https://pve.home.intranet:8006/api2/json/"
                          "nodes/pve/qemu/400/status/start")) {

              https.setAuthorization("PVEAPIToken=guest@pve!vmpower=%s", API::KEY);
              Log.infoln(F("Return code: %d"), https.POST("node=pve&vmid=400"));
              https.end();
          } else {
              Log.infoln("[HTTPS] Unable to connect");
          }
      }
      delete client;
  } else {
      Log.infoln("Unable to create client");
  }
  delay(60000);
}
