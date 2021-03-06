#include <dht.h>
#define DHT22_PIN 7

dht DHT;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float chk = DHT.read22(DHT22_PIN);
  Serial.print(DHT.temperature, 1);
  Serial.print(",");
  Serial.println(DHT.humidity, 1);
  delay(5000);
}
