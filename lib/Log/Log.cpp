#include <Arduino.h>
#include "Log.hpp"

void LOG::setup() {
  Log.begin(LEVEL, SINK);
  Log.notice(F("Logging started." CR));
  Log.notice(F("Log level: %d" CR), LOG_LEVEL);
}
