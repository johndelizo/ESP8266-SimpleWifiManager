#include "SimpleWifiManager.h" //// https://github.com/johndelizo/ESP8266-SimpleWifiManager

SimpleWifiManager simpleWifiManager;

void setup() {
  simpleWifiManager.Begin();
}

void loop() {
  simpleWifiManager.ProcessConnections();
}
