#include "Log.hpp"

namespace {
    __FlashStringHelper const* level2str(int level) {
      switch (level) {
      case 0:
        return F("NONE");
        break;
      case 1:
        return F("ERROR");
        break;
      case 2:
        return F("WARN");
        break;
      case 3:
        return F("INFO");
        break;
      case 4:
        return F("DEBUG");
        break;
      case 5:
        return F("VERBOSE");
        break;
      default:
        return F("UNKNOWN");
      }
    }
} // namespace

void LOG::setup() {
  __FlashStringHelper *level_str;

  Log.begin(LOG_DEFAULT_LEVEL, &SINK);
  Log.infoln(F(">>> Logging started."));
  Log.infoln(F("    --> Log level: %d (%S)"), Log.getLevel(), level2str(Log.getLevel()));
}
