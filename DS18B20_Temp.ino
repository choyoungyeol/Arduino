#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
uint8_t sensor1[8] = { 0x28, 0xFF, 0x6E, 0x73, 0x71, 0x17, 0x04, 0x7C };
uint8_t sensor2[8] = { 0x28, 0xFF, 0x2B, 0xFB, 0x71, 0x17, 0x04, 0x82 };
float Temp;
float Temp1;

void setup(void) {
  Serial.begin(9600);
  sensors.begin();
}

void loop(void) {
  sensors.requestTemperatures();
  Serial.print("Sensor 1: ");
  Temp = sensors.getTempC(sensor1);
  Serial.println(Temp);
  Serial.print("Sensor 1: ");
  Temp1 = sensors.getTempC(sensor2);
  Serial.println(Temp1);
  Serial.println();
  delay(1000);
}
