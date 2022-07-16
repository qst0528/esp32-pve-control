#include "config.hpp"
#include "credentials.hpp"

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
}
// put your setup code here, to run once:
void loop() {
  shell.executeIfInput();
  // put your main code here, to run repeatedly:
}
