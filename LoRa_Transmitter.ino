#include <LoRa.h>
#include <Sensirion.h>

const uint8_t dataPin  =  2;
const uint8_t clockPin =  3;

float temperature;
float humidity;
float dewpoint;

Sensirion tempSensor = Sensirion(dataPin, clockPin);

String outString = "";

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(868E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop()
{
  tempSensor.measure(&temperature, &humidity, &dewpoint);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Dewpoint: ");
  Serial.print(dewpoint);
  Serial.println(" C");

  delay(2000);
  outString = String(temperature) + "," + String(humidity) + "," + String(dewpoint);

  LoRa.beginPacket();
  LoRa.print(outString);
  LoRa.endPacket();
  delay(50);
}
