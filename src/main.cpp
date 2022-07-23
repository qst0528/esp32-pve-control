#include "config.hpp"
#include "HTTPClient.h"

namespace {
    void serialSetup(HardwareSerial &serial, unsigned long baud) {
        serial.begin(baud);
        serial.println(F("Booting PVE Control..."));
    }
    HTTPClient https;
} // namespace

void setup() {
    serialSetup(Serial, 115200);
    LOG::setup();
    CUI::attach();
    CUI::registerCUI();
    IP::init();
    https.setReuse(true);
    delay(5000);
}

// put your setup code here, to run once:
void loop() {
    shell.executeIfInput();
    // put your main code here, to run repeatedly:

    https.setAuthorization(API::TOKEN);
    https.begin("pve.home.intranet", 8006, "/api2/json/nodes/pve/qemu/400/status/start", (char *) SSL::root_ca_cert_start);
    https.POST("node=pve&vmid=400");
    https.end();
    delay(60000);
}
