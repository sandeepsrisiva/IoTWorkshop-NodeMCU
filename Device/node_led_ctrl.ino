#include <PubSubClient.h>
#include <ESP8266WiFi.h>


// Update these with values suitable for your network.

const char* ssid = "******"; // change to your home wifi name
const char* password = "*****"; //  change to your home wifi password
const char* mqtt_server = "iot.eclipse.org"; // MQTT broker Name


#define CLIENT_ID "*****" // Give your client id here


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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();


  //if ((char)payload[0] == 'o' && (char)payload[1] == 'n') 
   if ((char)payload[0] == '1')
  { // Here we are comparing if ON command is coming from server.

      digitalWrite(LED_BUILTIN, LOW);
    Serial.println("on");

  } else {
      digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("off");
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID

    // Attempt to connect
    if (client.connect(CLIENT_ID)) {
      Serial.println("connected");
      client.subscribe("led-ctr"); // your topic name
    }
  }
}

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.subscribe("*****"); // your topic name
  client.setCallback(callback);


}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}