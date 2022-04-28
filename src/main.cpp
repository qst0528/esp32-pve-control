#include "Arduino.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //PSRAM Initialisation
  if (psramInit()) {
    Serial.println("\nThe PSRAM is correctly initialized");
  } else {
    Serial.println("\nPSRAM does not work");
  }

  log_d("Total heap: %d", ESP.getHeapSize());
  log_d("Free heap: %d", ESP.getFreeHeap());
  log_d("Total PSRAM: %d", ESP.getPsramSize());
  log_d("Free PSRAM: %d", ESP.getFreePsram());
}

void loop() {
  // put your main code here, to run repeatedly:

}
