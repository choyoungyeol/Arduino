#include "DHT.h"
#include <DigitShield.h>

#define DHTPIN 12
#define DHTTYPE DHT11
#define Water_pin A0
#define Pump 10

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  DigitShield.begin();
  pinMode(Pump, OUTPUT);
}

void loop() {
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int Water_value = analogRead(Water_pin);
  int Water = map(Water_value, 1023, 357, 0, 100);
  Water = constrain(Water, 0, 100);
  DigitShield.setValue(t);
  delay(2000);
  DigitShield.setValue(h);
  delay(2000);
  DigitShield.setValue(Water);
  delay(2000);
  if (Water < 10) {
    digitalWrite(Pump, HIGH);
  } else {
    digitalWrite(Pump, LOW);
  }
}
