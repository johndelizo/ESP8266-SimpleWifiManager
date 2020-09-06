//// Simplified take on Arduino ESP8266 WiFi Management
//// https://github.com/johndelizo/ESP8266-SimpleWifiManager
//// by me[@]johndelizo.com 

#ifndef SimpleWifiManager_h
#define SimpleWifiManager_h
#include "Arduino.h"
#include "ConfigurableSerial.h"
#include <ESP8266WiFi.h>              //https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
#include <DNSServer.h>                //https://github.com/esp8266/Arduino/tree/master/libraries/DNSServer
#include <ESP8266WebServer.h>         //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer

class SimpleWifiManager {
  public:
    void Begin();
    void ProcessConnections();
  private:

    String global_projectName = "ESP8266-SimpleWiFiManager";
    int global_standardDelay = 3000;
    boolean global_serial_loggingEnabled = true;
    
    String wiFi_ap_initial_passkey = "hello123";
    IPAddress wiFi_ap_initial_IPAddress = IPAddress(11, 1, 1, 1);
    IPAddress wiFi_ap_initial_Gateway = IPAddress(11, 1, 1, 1);
    IPAddress wiFi_ap_initial_Subnet = IPAddress(255, 255, 255, 0);

    const String html_part1_header = "<!DOCTYPE HTML><html lang='en'><head><title>";
    const String html_part2_title = "</title><meta charset='utf-8' /><meta name='viewport' content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no'>";
    const String html_part3_style = "<style>body{background-color:#d1d7dc;font-family:sans-serif}*,*::before,*::after{box-sizing:inherit}html{box-sizing:border-box}.container{padding:0 10px;max-width:550px;margin:20px auto;font-size:18px;font-weight:600;line-height:36px}.inputGroup{background-color:#fff;display:block;margin:10px 0;position:relative}.inputGroup label{padding:12px 30px;width:100%;display:block;text-align:left;color:#3c454c;cursor:pointer;position:relative;z-index:2;-webkit-transition:color 200ms ease-in;transition:color 200ms ease-in;overflow:hidden}.inputGroup label:before{width:10px;height:10px;border-radius:50%;content:\"\";background-color:#5562eb;position:absolute;left:50%;top:50%;-webkit-transform:translate(-50%, -50%) scale3d(1, 1, 1);transform:translate(-50%, -50%) scale3d(1, 1, 1);-webkit-transition:all 300ms cubic-bezier(0.4, 0, 0.2, 1);transition:all 300ms cubic-bezier(0.4, 0, 0.2, 1);opacity:0;z-index:-1}.inputGroup label:after{width:32px;height:32px;content:\"\";border:2px solid #d1d7dc;background-color:#fff;background-image:url(\"data:image/svg+xml,%3Csvg width='32' height='32' viewBox='0 0 32 32' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath d='M5.414 11L4 12.414l5.414 5.414L20.828 6.414 19.414 5l-10 10z' fill='%23fff' fill-rule='nonzero'/%3E%3C/svg%3E \");background-repeat:no-repeat;background-position:2px 3px;border-radius:50%;z-index:2;position:absolute;right:30px;top:50%;-webkit-transform:translateY(-50%);transform:translateY(-50%);cursor:pointer;-webkit-transition:all 200ms ease-in;transition:all 200ms ease-in}.inputGroup input:checked~label{color:#fff}.inputGroup input:checked~label:before{-webkit-transform:translate(-50%, -50%) scale3d(56, 56, 1);transform:translate(-50%, -50%) scale3d(56, 56, 1);opacity:1}.inputGroup input:checked~label:after{background-color:#54e0c7;border-color:#54e0c7}.inputGroup input{width:32px;height:32px;-webkit-box-ordinal-group:2;order:1;z-index:2;position:absolute;right:30px;top:50%;-webkit-transform:translateY(-50%);transform:translateY(-50%);cursor:pointer;visibility:hidden}.button{background-color:#5562eb;display:block;position:relative;text-align:center;text-decoration:none;padding:15px 32px;color:white;border:none;font-size:12px}.header{display:flex;justify-content:space-between}.header a{background-color:#5562eb;display:block;position:relative;text-align:center;text-decoration:none;padding:0 15px;margin:15px 0;color:white;border:none;font-size:12px;height:40px}.header div{font-size:22px;padding:10px}.header .password{color:#54e0c7;letter-spacing:3px;font-size:18px;text-align:center}.connected { background-color: #5562eb; text-decoration: none; padding: 5px 15px; color: white; border: none; margin: 10px 0; }</style></head>";
    const String html_part4_body_template = "<body><div class='container'><form action=\"/connect\"><div class='header'><div>WiFi Connections</div> <a href='/refresh'>Refresh</a></div>";
    const String html_part5_body_connected_templatepart1 = "<body><div class='container'><form action=\"/connect\"><div class=\"connected\"><p>Connected to:</p><h2>";
    const String html_part5_body_connected_templatepart2 = "</h2></div><div class='header'><form action=\"/connect\"><div>WiFi Connections</div> <a href='/refresh'>Refresh</a></div>";
    const String html_Part7_script = "<div class=\"header\"> <input id=\"password\"  class=\"password\" name=\"password\" type=\"password\" placeholder=\"Enter Password\" /> <button type=\"submit\"  class=\"button\" id=\"connect\">Connect</button></div></form></div>";
    const String html_Part8_footer = "</body></html>";

    void onWebServerMainPage();
    void onWebServerConnectPage();
    void onWebServerNotFoundPage();
    void webServerRedirectToHome();
    void webServerSend(String htmlPage);
    void webServerSend(String htmlPage, int statusCode);
    String webServerScan();
    String webServerCurrentConnection();
    bool wiFiConnectWithRetry(String wifiSsid, String wifiPassword, int retryCount, int retryDelay);
    String ipAddressToString(IPAddress ip);
};

#endif
