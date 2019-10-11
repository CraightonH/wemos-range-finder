#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <HttpClient.h>

#define trigPin D3
#define echoPin D4

void findKnownWiFiNetworks() {
  ESP8266WiFiMulti wifiMulti;
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("BYU-WiFi", "");
  wifiMulti.addAP("Hancock2.4G", "Arohanui");
  Serial.println("");
  Serial.print("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    wifiMulti.run();
    delay(1000);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID().c_str());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(void) {
  Serial.begin(115200);
  findKnownWiFiNetworks();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void makeRequest(char *request) {
    HttpClient client;
    char *address = "http://10.37.125.55/stoplight/";
    char str[]
    client.get("http://10.37.125.55/stoplight/");
}

void loop(void) {
  Serial.println("working");
  delay(5000);
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delay(5);
  digitalWrite(trigPin, HIGH);
  delay(2);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)/29.1;
  if (distance <= 30) {
    
  }
}
