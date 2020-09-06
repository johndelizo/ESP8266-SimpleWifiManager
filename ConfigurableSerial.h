#ifndef ConfigurableSerial_h
#define ConfigurableSerial_h
#include "Arduino.h"

class ConfigurableSerial {
  public:
    void Begin(String prefix, int rate, boolean enabled);
    void Out();
    void Out(String input);
    void Out(String input, bool newline);
  private:
    String _prefix;
    boolean _enabled;
};

#endif
