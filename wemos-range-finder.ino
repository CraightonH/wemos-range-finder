#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <HttpClient.h>

const int TRIGPIN = D3;
const int ECHOPIN = D4;

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
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
}

void makeRequest(String request) {
    HttpClient client;
    String address = String("http://192.168.1.58/stoplight/" + request);
    Serial.println("Making the following request: " + address);
    client.get(address);
}

void loop(void) {
  Serial.println("working");
  delay(3000);
  /*
  long duration, distance;
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  Serial.println(String("duration measured: " + duration));
  distance = (duration/2) * .0344;
  Serial.println(String("distance calculated: " + distance));
  if (distance <= 10) {
    //makeRequest("red");
    Serial.println(String("Short distance"));
  }
  if (distance >= 10 && distance <= 20) {
    //makeRequest("yellow");
    Serial.println(String("Medium distance"));
  }
  if (distance > 20) {
    //makeRequest("green");
    Serial.println(String("Long distance"));
  }
  */
}
