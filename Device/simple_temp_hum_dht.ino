#include <dht.h>


dht dht11;

// Give any pin of your choice, check the board's pinout diagram for that.
#define DHT11_PIN 5


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(DHT11_PIN,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
dht11.read11(DHT11_PIN);
Serial.println("Temperature = ");
Serial.print(dht11.temperature);
Serial.println("Humidity = ");
Serial.print(dht11.humidity);
delay(1000);

}