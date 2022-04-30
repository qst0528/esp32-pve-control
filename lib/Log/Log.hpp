#include <Arduino.h>
#include <ArduinoLog.h>

namespace LOG {
  extern Print& SINK;
  extern int    LEVEL;
  extern void setup();
} // namespace LOG
