#include <Arduino.h>
#include <ArduinoLog.h>

namespace LOG {
  extern Print& SINK;
  extern int    LEVEL;
  void setup();
} // namespace LOG
