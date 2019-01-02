/*
  Created by Jacin Montava
  02/01/2019
*/
/* LIBRARIES */
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ssl_client.h>
#include <WifiLocation.h>

/* WIFI CONFIG */
const char* ssid     = "XXX";
const char* password = "XXX";
WiFiServer server(80);
WiFiClient client; // SSL client needed for both libraries

const char* googleApiKey = "XXX";
String ipAddress = "";
WifiLocation location(googleApiKey);

/* FUNCTIONS */
void initHardware() {
  Serial.begin(115200);
}

void setupWiFi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");

  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  ipAddress = ip.toString();

  server.begin();
}

void setup() {
  initHardware();
  delay(10);
  setupWiFi();
}

void loop() {
  location_t loc = location.getGeoFromWiFi();

  Serial.println("Location request data");
  Serial.println(location.getSurroundingWiFiJson());
  Serial.println("Latitude: " + String(loc.lat, 7));
  Serial.println("Longitude: " + String(loc.lon, 7));
  Serial.println("Accuracy: " + String(loc.accuracy));
  yield();
  delay(15000);
}
