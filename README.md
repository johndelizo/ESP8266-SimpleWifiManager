# ESP8266-SimpleWifiManager
Simplified take on Arduino ESP8266 WiFi Management

![ESP8266](https://user-images.githubusercontent.com/1830478/92316364-78d67c00-f025-11ea-910b-3858c502ed69.png)  

# Contents
 - [Project Goals](#project-goals)
 - [Quick start](#quick-start)
   - [Installation](#installation)
   - [Setup](#setup)
   - [Loop](#loop)
 - [Features](#features)
   - [x] [Captive Portal on connect](#features)
   - [x] [Always Available Configuration Portal](#features)
   - [x] [Scan for nearby WiFi](#features)
   - [x] [Connect ESP8266 to WiFi](#features)
   - [x] [Shows current connection](#features)
 - [Wishlist](#wishlist)
 - [Limitations](#limitations)
 - [Credits and Libraries Used](#credits-and-libraries-used)
 
 
## Project Goals!

- **Simple**. Plug and play with default configuration;
- **Clean Code**. Trying to and its a work in progress;
- **Standalone**. Only Arduino and ESP8266 libraries, no user or 3rd party dependencies should be used, besides my configurable serial which is just a toggle to enable or disable serial print line. 
- **Configurable** (soon), TODO: Add extension methods for personalization and update of configuration;
- **Fast** (soon), TODO: Refactor web server responses.

## Quick Start
**Include the library to your ESP8266 Sketch, initialize SimpleWifiManager and call two functions.**  

[![](https://user-images.githubusercontent.com/1830478/92315817-f4342f80-f01d-11ea-9ac2-7f4ded63199b.JPG)](https://user-images.githubusercontent.com/1830478/92315817-f4342f80-f01d-11ea-9ac2-7f4ded63199b.JPG)

### 1. Installation  

For now, you may include the following on the top of your Arduino Sketch file.
```cpp
#include "SimpleWifiManager.h" //// https://github.com/johndelizo/ESP8266-SimpleWifiManager
SimpleWifiManager simpleWifiManager;
```

### 2. Setup  

Setup should call the `.Begin()` method of SimpleWifiManager
```cpp
void setup() {
  simpleWifiManager.Begin();
}
```

### 3. Loop  

Still on your Arduino Sketch add the `.ProcessConnections()` method of SimpleWifiManager inside the Loop.
```cpp
void loop() {
  simpleWifiManager.ProcessConnections();
}

```

## Features
To get started, run or upload the sketch to your ESP8266. Once running, connect to ESP8266's WiFi SSID. By Default the SSID or connection name is "ESP8266-SimpleWiFiManager" with password "hello123".  The captive portal should launch after connecting. 

### Captive Portal
Simple WiFi Manager opens the Captive Portal on your phone after connecting to the ESP8266 WiFi. 

![Captive Portal](https://user-images.githubusercontent.com/1830478/92316316-b5ee3e80-f024-11ea-915d-fd45e533ef1c.png)

The same website used for captive portal is always available while your phone is connected to ESP8266 WiFi. 
By default, the address is "http://11.1.1.1/" 

### Always Available Configuration Portal
![Always Available Configuration Portal](https://user-images.githubusercontent.com/1830478/92316331-de763880-f024-11ea-976c-2f48c91726db.png)



## Wishlist
- [ ] Publish to Arduino Library 
- [ ] Publush to Platform.IO
- [ ] More Examples

## Limitations
- Tested only with NodeMCU V1 board. 
- Tested only with iPhone 6s+ and 7+. Chrome and Safari. (Captive Portal lauching and device responsiveness / auto sizing of website.

## Credits and Libraries Used
This project is made from the following Arduino and ESP8266 libraries:
- ESP8266WiFi https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
- DNSServer https://github.com/esp8266/Arduino/tree/master/libraries/DNSServer
- ESP8266WebServer https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer

[![](https://user-images.githubusercontent.com/1830478/92315964-33638000-f020-11ea-9c6c-510addd8bfe4.png)](https://user-images.githubusercontent.com/1830478/92315964-33638000-f020-11ea-9c6c-510addd8bfe4.png)
