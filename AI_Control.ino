#include <SoftwareSerial.h>

#define Light_On 4
#define Light_Off 5
#define Pump_On 6
#define Pump_Off 7
#define Windows_On 8
#define Windows_Off 9
#define Fan_On 10
#define Fan_Off 11

SoftwareSerial Bluetooth(0, 1);

void setup() {
  // put your setup code here, to run once:
  pinMode(Light_On, OUTPUT);
  pinMode(Light_Off, OUTPUT);
  pinMode(Pump_On, OUTPUT);
  pinMode(Pump_Off, OUTPUT);
  pinMode(Windows_On, OUTPUT);
  pinMode(Windows_Off, OUTPUT);
  pinMode(Fan_On, OUTPUT);
  pinMode(Fan_Off, OUTPUT);
  Serial.begin(9600);
  Bluetooth.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Bluetooth.available()) {
    delay(3);
    char c = Bluetooth.read();
    if (c == 'a') {
      digitalWrite(Light_On, HIGH);
      digitalWrite(Light_Off, LOW);
    }
    if (c == 'b') {
      digitalWrite(Light_On, LOW);
      digitalWrite(Light_Off, HIGH);
    }
    if (c == 'c') {
      digitalWrite(Pump_On, HIGH);
      digitalWrite(Pump_Off, LOW);
    }
    if (c == 'd') {
      digitalWrite(Pump_On, LOW);
      digitalWrite(Pump_Off, HIGH);
    }
    if (c == 'e') {
      digitalWrite(Windows_On, HIGH);
      digitalWrite(Windows_Off, LOW);
    }
    if (c == 'f') {
      digitalWrite(Windows_On, LOW);
      digitalWrite(Windows_Off, HIGH);
    }
    if (c == 'g') {
      digitalWrite(Fan_On, HIGH);
      digitalWrite(Fan_Off, LOW);
    }
    if (c == 'h') {
      digitalWrite(Fan_On, LOW);
      digitalWrite(Fan_Off, HIGH);
    }

    if (c == 'z') {
      digitalWrite(Light_On, LOW);
      digitalWrite(Light_Off, LOW);
      digitalWrite(Pump_On, LOW);
      digitalWrite(Pump_Off, LOW);
      digitalWrite(Windows_On, LOW);
      digitalWrite(Windows_Off, LOW);
      digitalWrite(Fan_On, LOW);
      digitalWrite(Fan_Off, LOW);
    }

  }
}
