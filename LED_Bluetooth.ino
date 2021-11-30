#include <SoftwareSerial.h>
#define LED 5

SoftwareSerial Bluetooth(2, 3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Bluetooth.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'a') {
      digitalWrite(LED, HIGH);
    }
    if (c == 'b') {
      digitalWrite(LED, LOW);
    }
  }

  if (Bluetooth.available()) {
    char c = Bluetooth.read();
    if (c == 'a') {
      digitalWrite(LED, HIGH);
    }
    if (c == 'b') {
      digitalWrite(LED, LOW);
    }
  }
}
