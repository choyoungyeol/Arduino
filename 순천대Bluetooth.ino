#include <DHT.h>
#include <SoftwareSerial.h>

#define dhtpin 12
#define dhttype DHT11
#define Pump 6

DHT dht(dhtpin, dhttype);
SoftwareSerial Bluetooth(0, 1);

void setup() {
  // put your setup code here, to run once:
  pinMode(Pump, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  Bluetooth.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int temp = dht.readTemperature();
  int humi = dht.readHumidity();

  //Serial.print("Temp = ");
  Serial.print(temp);
  //Serial.print("oC");
  Serial.print(", ");
  //Serial.print("Humi = ");
  Serial.println(humi);
  //Serial.println(" %");
  delay(2000);

  if (Bluetooth.available()) {
    delay(3);
    char c = Bluetooth.read();
    if (c == 'a') {
      digitalWrite(Pump, HIGH);
    }
    if (c == 'b') {
      digitalWrite(Pump, LOW);
    }
  }
}
