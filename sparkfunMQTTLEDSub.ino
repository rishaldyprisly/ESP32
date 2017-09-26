/*2017 SPARKFUN ESP 32 THING MQTT RGB LIGHT */
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "CHANGE THIS WITH YOUR WIFI ID";
const char* password = "WIFI PASSWORD";
const char* mqtt_server = "YOUR COMPUTER IP AS A BROKER";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
 // pinMode(D8, OUTPUT);     
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
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
  if ((char)payload[0] == '1') {
    digitalWrite(2, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } 
  if ((char)payload[0] == '0') {
    digitalWrite(2, LOW);  // Turn the LED off by making the voltage HIGH
  }

  if ((char)payload[0] == '3') {
    digitalWrite(4, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } 
  if ((char)payload[0] == '2') {
    digitalWrite(4, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } 

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("SPARK32Client")) {
      Serial.println("connected");
      client.subscribe("SPARKFUN");
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

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
