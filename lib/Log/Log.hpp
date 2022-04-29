#include <Arduino.h>
#include <ArduinoLog.h>

namespace LOG {
  extern Print     *SINK;
  extern const int  LEVEL;
  void setup();
} // namespace LOG
