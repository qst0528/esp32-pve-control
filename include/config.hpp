Print&          LOG::SINK      = Serial;
int             LOG::LEVEL     = 4;

Stream&         CUI::REQUESTER = Serial;

namespace WIFI {
extern const __FlashStringHelper *HOSTNAME;
extern const uint16_t             OTA_PORT;
extern const __FlashStringHelper *SSID;
extern const __FlashStringHelper *PASSPHRASE;
} // namespace WIFI
