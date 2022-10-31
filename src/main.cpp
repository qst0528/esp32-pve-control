#include "config.hpp"
#include "HTTPClient.h"
#include <ESP32TimerInterrupt.h>

namespace {
    HTTPClient https;
    volatile  int eventID    =  0;
    const uint8_t resume_pin = 18;
    const uint8_t start_pin  = 22;

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
    pinMode(resume_pin, INPUT_PULLUP);
    pinMode(start_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(resume_pin), func_resume, FALLING);
    attachInterrupt(digitalPinToInterrupt(start_pin), func_on, FALLING);
    pinMode(34, OUTPUT);
}

// put your setup code here, to run once:
void loop() {
    shell.executeIfInput();
    handleEvents();
}
