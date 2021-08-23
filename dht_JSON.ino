#include <dht.h>
#define DHT22_PIN 7

dht DHT;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float chk = DHT.read22(DHT22_PIN);
  Serial.print("{\"Sensor1\":");
  Serial.print(DHT.temperature, 1);
  Serial.print(",\"Sensor2\":");
  Serial.print(DHT.humidity, 1);
  Serial.println("}");
  delay(5000);
}
