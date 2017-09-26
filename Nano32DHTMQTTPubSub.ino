/*2017 - NANO 32 DHT AND LED MQTT 
RISHALDY PRISLY */
#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>
#define DHTPIN 27
#define DHTTYPE DHT11

const char* ssid = "YOUR WIFI ID";
const char* password = "WIFI PASSWORD";
const char* mqtt_server = "YOUR COMPUTER'S IP AS A BROKER";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
 // pinMode(D8, OUTPUT);     
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  dht.begin();
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (char i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

 
  // Switch on the GPIO if an 1 was received as first character
  if ((char)payload[0] == '0') {
    digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } 
  if ((char)payload[0] == '1') {
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off by making the voltage HIGH
  }

/*  if ((char)payload[0] == '3') {
    digitalWrite(D8, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } 
  if ((char)payload[0] == '2') {
    digitalWrite(D8, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } */

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Nano32Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("test", "hello world");
      // ... and resubscribe
      client.subscribe("NANO32");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
    // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  client.publish("test", String(t).c_str());
  client.publish("test", String(h).c_str());
  delay(5000);
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  /*long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }*/
}
