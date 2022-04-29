#include <Arduino.h>
#include <SimpleSerialShell.h>

namespace CUI {
  extern Stream& REQUESTER;
  typedef struct LookupVals lookupVals;
  int  lookup(const char *, const lookupVals[]);
  void attach();
  void registerCUI();
} // namespace CUI
