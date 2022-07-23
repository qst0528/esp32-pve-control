#include "config.hpp"
#include "HTTPClient.h"

namespace {
    HTTPClient https;
    int dirty = 0;

    void serialSetup(HardwareSerial &serial, unsigned long baud) {
        serial.begin(baud);
        serial.println(F("Booting PVE Control..."));
    }

    void sendVMStart() {
      https.setAuthorization(PVE::TOKEN);
      https.begin(PVE::HOST, PVE::PORT,
                  "/api2/json/nodes/pve/qemu/400/status/start",
                  (char *)SSL::root_ca_cert_start);
      https.POST("node=pve&vmid=400");
      https.end();
    }

    void func_on() {
        noInterrupts();
        dirty = 1;
        interrupts();
    }
} // namespace


void setup() {
    serialSetup(Serial, 115200);
    LOG::setup();
    CUI::attach();
    CUI::registerCUI();
    IP::init();
    https.setReuse(true);
    pinMode(22, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(22), func_on, FALLING);
}

// put your setup code here, to run once:
void loop() {
    shell.executeIfInput();
    // put your main code here, to run repeatedly:
    if (dirty) {
        Serial.write("Pushed\n");
        sendVMStart();
        dirty = 0;
    }
}
