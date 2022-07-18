#include <Arduino.h>
#include <CUI.hpp>
#include <Log.hpp>
#include <IP.hpp>

namespace API {
  extern char const* KEY;
}

namespace SSL {
  extern const uint8_t root_ca_cert_start[]
  asm("_binary_src_certs_root_ca_pem_start");
  extern const uint8_t root_ca_cert_end[]
  asm("_binary_src_certs_root_ca_pem_end");
  extern const uint8_t ssl_pub_start[]
  asm("_binary_src_certs_ssl_pub_pem_start");
  extern const uint8_t ssl_pub_end[]
  asm("_binary_src_certs_ssl_pub_pem_end");
}; // namespace SSL
