#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DHTPIN 17
#define DHTTYPE DHT11 
DHT dht(DHTPIN,DHTTYPE);

const char server[] = "your server"; 

const char* MY_SSID = "SSID / WiFi";
const char* MY_PWD =  "WiFi Password";

WiFiClient client;


void setup()
{
  Serial.begin(115200);
  dht.begin();
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");

  while (WiFi.status() != WL_CONNECTED) //not connected,  ...waiting to connect
    {
      delay(1000);
      Serial.print(".");
    }
  Serial.println("wl connected");
  Serial.println("");
  Serial.println("Credentials accepted! Connected to wifi\n ");
  Serial.println("");
}

void loop() {

   // Wait a few seconds between measurements.
  delay(2000);

  //prefer to use float, but package size or float conversion isnt working
  //will revise in future with a string fuction or float conversion function

  int humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int temperature = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  char location[] = "DeckA";

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  //int HeatIndex_Fehr = dht.computeHeatIndex(Temperature, Humidity);
  // Compute heat index in Celsius (isFahreheit = false)
 // int HeatIndex_Cel = dht.computeHeatIndex(Temperature_Cel, Humidity, false);

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C ");
  Serial.print(location);
  Serial.print(" \t");


    Serial.println("\nStarting connection to server..."); 
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    WiFi.printDiag(Serial);

    String data = "temperature="
          +               (String) temperature
          +  "&humidity="+(String) humidity
          +  "&location="+(String) location;
         // http://proto.sparks.id/post.php?temperature=90&humidity=2&location=C

     //change URL below if using your Sub-Domain
     client.println("POST /post.php HTTP/1.1"); 
     //change URL below if using your Domain
     client.print("Host: proto.sparks.id\n");                 
     client.println("User-Agent: NANO32/1.0");
     client.println("Connection: close"); 
     client.println("Content-Type: application/x-www-form-urlencoded");
     client.print("Content-Length: ");
     client.print(data.length());
     client.print("\n\n");
     client.print(data);
     client.stop(); 
     
     Serial.println("\n");
     Serial.println("My data string im POSTing looks like this: ");
     Serial.println(data);
     Serial.println("And it is this many bytes: ");
     Serial.println(data.length());       
     delay(600000);
    } 

}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
