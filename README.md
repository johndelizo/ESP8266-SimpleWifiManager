# ESP8266-SimpleWifiManager
Simplified take on Arduino ESP8266 WiFi Management

## Contents
 - [Project Goals](#project-goals)
 - [Quick start](#quick-start)
 - [Features](#features)
 - [Wishlist](#wishlist)
 - [Credits and Libraries Used](#credits-and-libraries-used)
 
 
### Project Goals!

- **Simple**. Plug and play with default configuration;
- **Clean Code**. Trying to and its a work in progress;
- **Standalone**. Only Arduino and ESP8266 libraries, no user or 3rd party dependencies should be used, besides my configurable serial which is just a toggle to enable or disable serial print line. 
- **Configurable** (soon), TODO: Add extension methods for personalization and update of configuration;
- **Fast** (soon), TODO: Refactor web server responses.

### Quick Start
**Include the library to your ESP8266 Sketch, initialize SimpleWifiManager and call two functions.**  

[![](https://user-images.githubusercontent.com/1830478/92315817-f4342f80-f01d-11ea-9ac2-7f4ded63199b.JPG)](https://user-images.githubusercontent.com/1830478/92315817-f4342f80-f01d-11ea-9ac2-7f4ded63199b.JPG)
  

### Features
- [x] Captive Portal on connect
- [x] Always Available Configuration Portal 
- [x] Scan for nearby WiFi
- [x] Connect ESP8266 to WiFi
- [x] Shows current connection

### Wishlist
- [ ] Publish to Arduino Library 
- [ ] Publush to Platform.IO
- [ ] More Examples

### Credits and Libraries Used
This project is made from the following Arduino and ESP8266 libraries:
- ESP8266WiFi https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
- DNSServer https://github.com/esp8266/Arduino/tree/master/libraries/DNSServer
- ESP8266WebServer https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer

[![](https://user-images.githubusercontent.com/1830478/92315964-33638000-f020-11ea-9c6c-510addd8bfe4.png)](https://user-images.githubusercontent.com/1830478/92315964-33638000-f020-11ea-9c6c-510addd8bfe4.png)
