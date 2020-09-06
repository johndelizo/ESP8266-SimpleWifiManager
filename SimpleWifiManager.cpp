//// Simplified take on Arduino ESP8266 WiFi Management
//// https://github.com/johndelizo/ESP8266-SimpleWifiManager
//// by me[@]johndelizo.com

#include "SimpleWifiManager.h"

DNSServer dnsServer;
ESP8266WebServer webServer(80);
ConfigurableSerial cSerial;

void SimpleWifiManager::Begin() {

  cSerial.Begin(global_projectName, 115200, global_serial_loggingEnabled);
  cSerial.Out("-- Start");
  cSerial.Out("--- Start - Act as an access point (AP)");
  WiFi.persistent(true);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(wiFi_ap_initial_IPAddress, wiFi_ap_initial_Gateway, wiFi_ap_initial_Subnet);
  WiFi.softAP(global_projectName, wiFi_ap_initial_passkey);
  cSerial.Out("--- Start - WiFi-Begin - TurnOn Wireless using last config from flash memory (WiFi)");
  //https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/station-class.html?highlight=WiFi.begin#begin
  WiFi.begin();
  delay(global_standardDelay);

  cSerial.Out("--- Start - Name Server start (DNS)");
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(53, "*", WiFi.softAPIP());
  delay(global_standardDelay);;

  cSerial.Out("--- Start - Web Server start");
  //c-unresolved-overloaded-function-type
  //https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type
  webServer.on("/", [this]() {
    onWebServerMainPage();
  });
  webServer.on("/refresh", [this]() {
    onWebServerMainPage();
  });
  webServer.on("/connect", [this]() {
    onWebServerConnectPage();
  });
  webServer.onNotFound([this]() {
    onWebServerNotFoundPage();
  });
  webServer.begin();
  delay(global_standardDelay);;

  cSerial.Out("-- Start Complete, Server ready");
}

void SimpleWifiManager::ProcessConnections() {
  dnsServer.processNextRequest();
  webServer.handleClient();
  delay(global_standardDelay);;
}

void SimpleWifiManager::onWebServerMainPage() {
  cSerial.Out("-- onWebServerMainPage");

  String webServer_hostHeader = webServer.hostHeader();
  cSerial.Out("--- onWebServerMainPage - HostHeader: " + webServer_hostHeader);
  
  //https://github.com/esp8266/Arduino/blob/master/libraries/DNSServer/examples/CaptivePortalAdvanced/handleHttp.ino
  if (webServer_hostHeader != ipAddressToString(wiFi_ap_initial_IPAddress)){
    cSerial.Out("--- onWebServerMainPage - User redirect back home");
    webServerRedirectToHome();
    return;
  }

  String html_part4_body = webServerCurrentConnection();
  String html_part6_content = webServerScan();

  String htmlPage = html_part1_header + global_projectName + html_part2_title  + html_part3_style + html_part4_body + html_part6_content + html_Part7_script + html_Part8_footer;

  webServerSend(htmlPage);
}

void SimpleWifiManager::onWebServerNotFoundPage() {
  cSerial.Out("-- onWebServerNotFoundPage");

  String webServer_hostHeader = webServer.hostHeader();
  cSerial.Out("--- onWebServerNotFoundPage - HostHeader: " + webServer_hostHeader);
  
  if (webServer_hostHeader != ipAddressToString(wiFi_ap_initial_IPAddress)){
    cSerial.Out("--- onWebServerNotFoundPage - User redirect back home");
    webServerRedirectToHome();
    return;
  }

  String html_part6_content = "<h1>Content not found!<h1>";
  String htmlPage = html_part1_header + global_projectName + html_part2_title  + html_part4_body_template + html_part6_content +  html_Part8_footer;

  webServerSend(htmlPage, 404);
}

void SimpleWifiManager::onWebServerConnectPage() {
  cSerial.Out("-- onWebServerConnectPage");

  String wifi_new_ssId = webServer.arg("wifichoice");
  String wifi_new_password = webServer.arg("password");

  cSerial.Out("--- onWebServerConnectPage - wifi_new_ssId: " + wifi_new_ssId);
  cSerial.Out("--- onWebServerConnectPage - wifi_new_password: " + wifi_new_password);

  boolean wiFiConnectWithRetry_Success = wiFiConnectWithRetry(wifi_new_ssId, wifi_new_password, 5, 6000);

  if (wiFiConnectWithRetry_Success) {
    cSerial.Out("--- onWebServerConnectPage - wiFiConnectWithRetry Success - webServerRedirectToHome");
  }
  else {
    cSerial.Out("--- onWebServerConnectPage - wiFiConnectWithRetry Fail - responding with HTML Page");
  }

  webServerRedirectToHome();
}

void SimpleWifiManager::webServerRedirectToHome() {
  cSerial.Out("-- webServerRedirectToHome");
  String ap_IpAddress = ipAddressToString(wiFi_ap_initial_IPAddress);
  cSerial.Out("-- webServerRedirectToHome - 302 Redirect to " + ap_IpAddress);
  webServer.sendHeader("Location", "http://" + ap_IpAddress, true);
  webServer.send(302, "text/plain", "");
  webServer.client().stop();
}

void SimpleWifiManager::webServerSend(String htmlPage) {
  webServerSend(htmlPage, 200);
}

void SimpleWifiManager::webServerSend(String htmlPage, int statusCode) {
  cSerial.Out("-- webServerSend");
  cSerial.Out("--- webServerSend Status Code: " + String(statusCode));
  //cSerial.Out(htmlPage); //For Debugging Purposes. 

   String webServer_hostHeader = webServer.hostHeader();
  cSerial.Out("--- webServerSend - Client requesting for: " + webServer_hostHeader);

  int htmlPage_length = htmlPage.length();

  cSerial.Out("--- webServerSend - Started Sending: " + String(htmlPage_length));
  //Webpage Caching
  //https://stackoverflow.com/questions/49547/how-do-we-control-web-page-caching-across-all-browsers
  webServer.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  webServer.sendHeader("Pragma", "no-cache");
  webServer.sendHeader("Expires", "0");
  webServer.sendHeader("Content-Length", String(htmlPage_length));
  webServer.send(statusCode, "text/html", htmlPage);

  if (htmlPage_length == 0) {
    cSerial.Out("--- webServerSend - content legth is zero, must stop web server client");
    webServer.client().stop();
  }
}

String SimpleWifiManager::webServerScan() {
  cSerial.Out("-- webServerScan");
  int networkCount = WiFi.scanNetworks();

  cSerial.Out("--- webServerScan - Found Number of broadcasting wifi: " + String(networkCount));

  String wifiChoices = "";

  for (int i = 0; i < networkCount; i++) {
    String wifiSSID = WiFi.SSID(i);
    wifiChoices = wifiChoices + "<div class='inputGroup'><input id='" + wifiSSID + "' value='" + wifiSSID + "' name='wifichoice' type='radio'/><label for='" + wifiSSID + "'>" + wifiSSID + "</label></div>";
  }
  return wifiChoices;
}

String SimpleWifiManager::webServerCurrentConnection() {
  cSerial.Out("-- webServerCurrentConnection");
  if (WiFi.status() == WL_CONNECTED) {
    cSerial.Out("--- webServerCurrentConnection - WiFi Connected");
    cSerial.Out("--- webServerCurrentConnection - WiFi Connected to: " + WiFi.SSID());
    return html_part5_body_connected_templatepart1 + WiFi.SSID() + html_part5_body_connected_templatepart2;
  }
  else {
    cSerial.Out("--- webServerCurrentConnection - WiFi Not Connected");
    return html_part4_body_template;
  }
}

bool SimpleWifiManager::wiFiConnectWithRetry(String wifiSsid, String wifiPassword, int retryCount, int retryDelay) {
  cSerial.Out("-- wiFiConnectWithRetry");

  if (WiFi.status() == WL_CONNECTED) {
    cSerial.Out("--- wiFiConnectWithRetry - WL_CONNECTED - Disconnect to current network");
    WiFi.disconnect();
  }

  while (retryCount >= 1) {
    cSerial.Out("--- wiFiConnectWithRetry - WiFi.begin");
    int wiFi_begin_status = WiFi.begin(wifiSsid, wifiPassword);
    delay(retryDelay);
    //Use WiFi.status instead of Wifi.begin response.
    //https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
    if (WiFi.status() == WL_CONNECTED) {
      cSerial.Out("--- wiFiConnectWithRetry - WiFi.begin - Connected!");
      return true;
    }
    else {
      retryCount--;
      cSerial.Out("--- wiFiConnectWithRetry - WiFi.begin - Not Connected, Retry left: " + String(retryCount));
      delay(retryDelay);
    }
  }
  cSerial.Out("--- wiFiConnectWithRetry - WiFi.begin - Retry exhausted, will exit.");
  return false;
}

String SimpleWifiManager::ipAddressToString(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}
