#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#include <dht.h>


// Give any pin of your choice, check the board's pinout diagram for that.
#define DHT11_PIN 5

#define CLIENT_ID "******" // Give your client id name
#define PUB_TOPIC "*******" // Give your publishing topic name

// Update these with values suitable for your network.

const char* ssid = "*******"; // change to your home wifi name
const char* password = "*******"; //  change to your home wifi password
const char* mqtt_server = "iot.eclipse.org"; // MQTT broker Name 

dht dht11;


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
  

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

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void setup() {


  Serial.begin(9600);

  pinMode(DHT11_PIN,INPUT);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  
}

void loop() {

  String temp;
  String hum;
  String temp_hum;
  char mesg[20];

  dht11.read11(DHT11_PIN);
  Serial.println("Temperature = ");
  
  Serial.print(dht11.temperature);
  temp_hum+="Temp-";
  temp_hum += String(dht11.temperature);   

  Serial.println("Humidity = ");
  
  Serial.print(dht11.humidity);
  temp_hum+=",Hum-";
  temp_hum += String(dht11.humidity);
    
  temp_hum.toCharArray(mesg,20);  

  if (client.connect(CLIENT_ID)){

      Serial.println("sending message to the mobile app");
      client.publish(PUB_TOPIC,mesg);

  }



  delay(3000);


}