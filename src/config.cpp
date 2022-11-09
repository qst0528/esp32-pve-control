#include "config.hpp"

Print&          LOG::SINK      = Serial;

Stream&         CUI::REQUESTER = Serial;

char     const* IP::HOSTNAME   = "pve-control";
uint16_t        IP::OTA_PORT   = 8266;
