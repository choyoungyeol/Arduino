#include "DHT.h"
#define DHTPIN A1
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print(t, 1);
  Serial.print(",");
  Serial.println(h, 1);
  delay(5000);
}
