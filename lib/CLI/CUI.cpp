#include "CUI.hpp"
#include "Log.hpp"

namespace {
int printVersion(int argc = 0, char **argv = nullptr) {
  shell.println(F(">>> PVE Control"));
  shell.println(F("    --> Git revision: " GIT_REV));
  shell.println(F("    --> Build date:   " __DATE__));
  return EXIT_SUCCESS;
}
} // namespace

struct CUI::LookupVals {
    char *name;
    int val;
};

int CUI::lookup(const char *aName, const CUI::lookupVals entries[]) {
  int i = 0;
  for (; entries[i].name; i++) {
    if (strncasecmp(aName, entries[i].name, 20) == 0) {
      break;
    }
  }
  return entries[i].val;
}

void CUI::attach() {
  Log.infoln(F(">>> Attaching SimpleShell to Serial..."));
  shell.attach(REQUESTER);
  Log.infoln(F("    --> SimpleShell attached."));
  Log.infoln(F("    --> Type \"help\" to get list of commands."));
}

void CUI::registerCUI() {
  Log.infoln(F(">>> Adding basic CLI commands..."));
  shell.addCommand(F("version"), printVersion);
}
