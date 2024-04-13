void createSSID() {
  uint64_t chipid = ESP.getEfuseMac(); //The chip ID is essentially its MAC address(length: 6 bytes).
  uint16_t chipno1 = (uint16_t)(chipid >> 32);
  uint16_t chipno2 = (uint32_t)chipid;
  snprintf(uniquename, 15, "%08X", chipno1);
  snprintf(uniqueid, 15, "%04X", chipno2);
  id = (String)uniquename + (String)uniqueid;
}
