#include <dht.h>


// Robo India Tutorial 
// Simple code upload the tempeature and humidity data using thingspeak.com
// Hardware: NodeMCU,DHT11

//#include <DHT.h>  // Including library for dht

#include <ESP8266WiFi.h>
 


const char *ssid =  "xxxxxxx";     // replace with your wifi ssid and wpa2 key
const char *pass =  "xxxxxxxxx";
const char* server = "xxxxxxxx";

#define DHTPIN D0          //pin where the dht11 is connected
 
//DHT dht(DHTPIN, DHT11);
dht DHT11;

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       //dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
     DHT11.read11(DHTPIN);

      if (!client.connect(server, 80)) {
          Serial.println("connection failed");
          return;
       }
      float h = DHT11.humidity;
      float t = DHT11.temperature;
      
      if (isnan(h) || isnan(t)) 
      {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }
      client.print(String("GET /cry/index.php?r=") + String(t) + "x" + String(h) + " HTTP/1.1\r\n" +"Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
      delay(10);
                    
                    // Read all the lines of the reply from server and print them to Serial
      while(client.available()){
        //Serial.println("client avaialble"); 
        String line = client.readStringUntil('\r');
        Serial.print(line);
      }

 
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.print(" degrees Celcius, Humidity: ");
      Serial.println(h);
      Serial.println("Waiting...");
  
  
  delay(10000);
}
