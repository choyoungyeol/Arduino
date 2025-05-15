#include "DHT.h"
#define DHTPIN A1
#define DHTTYPE DHT22
#define Fan 29
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(Fan, OUTPUT);
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (Serial.available()) {
    delay(3);
    char c = Serial.read();
    if (c == 'a') {
      digitalWrite(Fan, HIGH);
    }
    if (c == 'b') {
      digitalWrite(Fan, LOW);
    }
  }
  Serial.print(t, 1);
  Serial.print(",");
  Serial.println(h, 1);
  delay(2000);
}
