#include <Arduino.h>
#include <ArduinoLog.h>

namespace LOG {
  extern Print& SINK;
  extern int    LEVEL;
  extern void setup();
  extern __FlashStringHelper const* level2str(int);
} // namespace LOG
