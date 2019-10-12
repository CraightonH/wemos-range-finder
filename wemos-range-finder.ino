#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoHttpClient.h>

const int TRIGPIN = D3;
const int ECHOPIN = D4;
WiFiClient wifi;
HttpClient client = HttpClient(wifi, "192.168.1.58", 80);

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
    String fullGet = String("/stoplight/" + request);
    Serial.println("Making the following request: " + fullGet);
    client.get(fullGet);
    if (client.responseStatusCode() == 200) {
      String response = client.responseBody();
      Serial.println(String("Responding with :" + response));
    } else {
      Serial.println(String("failed GET (response): " + client.responseStatusCode()));
    }
}

void loop(void) {
  Serial.println("working");
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
    Serial.println(String("Short distance"));
    makeRequest("red");
  }
  if (distance >= 10 && distance <= 20) {
    Serial.println(String("Medium distance"));
    makeRequest("yellow");
  }
  if (distance > 20) {
    Serial.println(String("Long distance"));
    makeRequest("green");
  }
}
