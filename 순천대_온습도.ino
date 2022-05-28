#include <DHT.h>

#define dhtpin 12
#define dhttype DHT11

DHT dht(dhtpin, dhttype);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();

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
}
