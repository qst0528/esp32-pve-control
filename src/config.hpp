#include "CUI.hpp"
#include "Log.hpp"
#include "IP.hpp"

Print&          LOG::SINK      = Serial;
int             LOG::LEVEL     = CORE_DEBUG_LEVEL;

Stream&         CUI::REQUESTER = Serial;

char     const* IP::HOSTNAME   = "pve-control";
uint16_t        IP::OTA_PORT   = 8266;
