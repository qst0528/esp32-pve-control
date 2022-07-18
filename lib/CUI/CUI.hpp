#include <Arduino.h>
#include <SimpleSerialShell.h>

namespace CUI {
  extern Stream& REQUESTER;
  typedef struct LookupVals lookupVals;
  extern int  lookup(char const*, const lookupVals[]);
  extern void attach();
  extern void registerCUI();
} // namespace CUI
