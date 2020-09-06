#include "ConfigurableSerial.h"
#include "Arduino.h"

void ConfigurableSerial::Begin(String prefix, int rate, boolean enabled) {
  _prefix  = prefix;
  _enabled = enabled;
  
  if(_enabled) {
    Serial.begin(rate);
    delay(3000);;
    Out("-------------------------------");
    Out(prefix + " Starting..");
    Out("-------------------------------");
  }
}

void ConfigurableSerial::Out(String input, bool newline) {
  if (_enabled) {
    input = _prefix + ": " +  input;
    if (newline) {
      Serial.println(input);
    }
    else {
      Serial.print(input);
    }
  }
}

void ConfigurableSerial::Out(String input) {
   Out(input, true);
}

void ConfigurableSerial::Out() {
   Out("", true);
}
