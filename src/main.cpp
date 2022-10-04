#include "config.hpp"
#include "HTTPClient.h"

namespace {
    HTTPClient https;
    volatile int eventID = 0;

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

    void sendVMResume() {
      https.setAuthorization(PVE::TOKEN);
      https.begin(PVE::HOST, PVE::PORT,
                  "/api2/json/nodes/pve/qemu/400/status/resume",
                  (char *)SSL::root_ca_cert_start);
      https.POST("node=pve&vmid=400");
      https.end();
    }

    void func_on() {
        noInterrupts();
        eventID = 1;
        interrupts();
    }

    void func_resume() {
        noInterrupts();
        eventID = 2;
        interrupts();
    }

    void handleEvents() {
      switch (eventID) {
      case 0:
        break;
      case 1:
        sendVMStart();
        break;
      case 2:
        sendVMResume();
        break;
      }
      eventID = 0;
    }
} // namespace


void setup() {
    serialSetup(Serial, 115200);
    LOG::setup();
    CUI::attach();
    CUI::registerCUI();
    IP::init();
    https.setReuse(true);
    pinMode(18, INPUT_PULLUP);
    pinMode(22, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(18), func_resume, FALLING);
    attachInterrupt(digitalPinToInterrupt(22), func_on, FALLING);
}

// put your setup code here, to run once:
void loop() {
    shell.executeIfInput();
    handleEvents();
}
